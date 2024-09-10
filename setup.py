#!/usr/bin/env python
# -*- coding: utf-8 -*-

import contextlib
import json
import mimetypes
import os
import platform
import re
import shutil
import sys
import sysconfig
import tarfile
import zipfile

if sys.version_info >= (3, 0):
    from urllib.error import URLError
    from urllib.request import urlopen, urlretrieve

    from setuptools import Command, Extension, setup
    from setuptools.command.build_ext import build_ext as BuildExtension
else:
    from distutils.command.build_ext import build_ext as BuildExtension
    from distutils.core import Command, Extension, setup
    from urllib import urlretrieve

    from urllib2 import URLError, urlopen

if sys.version_info >= (3, 5):
    from typing import Any
    from collections.abc import Iterator

BASE_DIR = os.path.dirname(os.path.realpath(__file__))


def get_option(name, default="", args=None):
    # type: (str, str, Iterator[str] | None) -> str
    if args is None:
        args = iter(sys.argv[1:])
    for opt in args:
        if opt.endswith(name):
            default = default if default else "1"
            arg = next(args, default)
            if arg and arg[0] != "-":
                return arg
            return default
    return default


RAYLIB_VERSION = get_option("raylib-version", "5.0")

mimetypes.add_type("text/markdown", ".md")
mimetypes.add_type("text/x-rst", ".rst")


def get_long_description():
    # type: () -> tuple[str, str]
    """Returns long_description's (content-type, content)"""
    try:
        base_dir_list = os.listdir(BASE_DIR)
    except OSError:
        return "UNKNOWN", "UNKNOWN"

    for file in base_dir_list:
        if file.upper().startswith("README"):
            break
    else:
        return "UNKNOWN", "UNKNOWN"

    try:
        with open(os.path.join(BASE_DIR, file), "r") as fp:
            content = fp.read()
    except OSError:
        content = "UNKNOWN"

    return (mimetypes.guess_type(file)[0] or "UNKNOWN", content)


def get_platform(plat=None, arch=None):
    # type: (str | None, str | None) -> str
    """Returns a raylib-releases-like platform name"""
    if plat is None:
        plat = sys.platform

    bit64 = platform.architecture()[0] == "64bit"

    if "linux" in plat:
        plat = "linux"
        if arch is None:
            arch = "amd64" if bit64 else "i386"

    if plat == "darwin":
        return "macos"

    if plat == "win32":
        if arch is None:
            arch = "mingw-w64" if sysconfig.get_platform() == "mingw" else "msvc16"
        if bit64:
            plat = "win64"

    if arch:
        plat += "_%s" % arch

    return plat


PLATFORM = get_option("plat-name", get_platform())


@contextlib.contextmanager
def fetch(url):
    # type: (str) -> Iterator[Any]
    """contextmanager for urlopen. riases `FetchError` on error"""
    sys.stderr.write("fetching %s\n" % url)
    try:
        fp = urlopen(url)
        try:
            yield fp
        finally:
            fp.close()
    except URLError as exc:
        raise FetchError(exc.reason, url, exc.filename)


class FetchError(URLError):
    def __init__(self, reason, uri, filename=None):
        # type: (str | BaseException, str, str | None) -> None
        super(FetchError, self).__init__(reason)
        self.uri = uri
        if filename is not None:
            self.filename = filename

    def __str__(self):  # type: () -> str
        return "<fetch error: %s: %s>" % (self.uri, self.reason)


class Log:
    DEBUG = 1
    INFO = 2
    WARN = 3
    ERROR = 4
    FATAL = 5


RAYLIB_DIR = os.path.join(BASE_DIR, ("build/deps.%s/raylib-%s/" % (PLATFORM, RAYLIB_VERSION)))


class DownloadDependencies(Command):

    GH_API_BASE_URI = "https://api.github.com"

    description = "Downloads build-dependencies (includes, libs, etc...)"

    user_options = [
        ("repo-fullname=", "r",
         "GitHub repository fullname as '{owner}/{user}' (default: raysan5/raylib)"),
        ("raylib-version=", "v",
         "raylib version to download (default: latest)"),
        ("plat-name=", "p",
         "platform name regex to downlaod for (default: %s)" % (PLATFORM)),
        ("no-semver", "n",
         "don't format raylib-version to X.0.0 or X.Y.0")
    ]

    def initialize_options(self):  # type: () -> None
        self.repo_fullname = "raysan5/raylib"
        self.raylib_version = RAYLIB_VERSION
        self.plat_name = PLATFORM
        self.no_semver = 0

    def finalize_options(self):  # type: () -> None
        pass

    def run(self):  # type: () -> None
        repo_url = "%s/repos/%s" % (self.GH_API_BASE_URI, self.repo_fullname)

        releases_url = repo_url + "/releases"
        assets_url = None

        if not self.raylib_version:
            with fetch(releases_url + "/latest") as response:
                data = json.load(response)
            self.raylib_version = data["tag_name"]
            assets_url = data["assets_url"]
            self.announce(
                "latest '%s' release is '%s'" % (self.repo_fullname, self.raylib_version), Log.INFO
            )

        if os.path.isdir(RAYLIB_DIR):
            self.announce("output directory '%s' already exist" % (RAYLIB_DIR), Log.INFO)
            return

        if assets_url is None:
            with fetch("%s/tags/%s" % (releases_url, self.raylib_version)) as response:
                assets_url = json.load(response)["assets_url"]

        with fetch(assets_url) as response:
            assets = json.load(response)  # type: list[dict[str, Any]]

        plat_name_pattern = re.compile(
            self.plat_name.replace("_", r"(_|-)").replace("16", r"(16|15)")
            if self.plat_name == PLATFORM
            else self.plat_name,
            re.IGNORECASE
        )

        for asset in assets:
            if plat_name_pattern.search(asset["name"]) is not None:
                break
        else:
            self.announce(
                "there's no raylib '%s' for '%s'" % (self.raylib_version, self.plat_name), Log.FATAL
            )
            return

        self.mkpath(RAYLIB_DIR)

        self.announce("downloading '%s'" % asset["name"], Log.INFO)
        archive, _ = urlretrieve(asset["browser_download_url"])

        _, ext = os.path.splitext(asset["name"])

        self.announce("unpacking archive to '%s'" % RAYLIB_DIR, Log.INFO)
        self.unpack_archive(archive, RAYLIB_DIR, "zip" if ext == ".zip" else "tar")

        out_dir_list = os.listdir(RAYLIB_DIR)

        if len(out_dir_list) > 1:
            return

        real_out_dir = os.path.join(RAYLIB_DIR, out_dir_list[0])
        self.move_tree(real_out_dir, RAYLIB_DIR)
        os.rmdir(real_out_dir)

    def move_tree(self, src, dst):
        # type: (str, str) -> None
        self.announce("moving tree '%s' to '%s'" % (src, dst), Log.INFO)
        for child in os.listdir(src):
            shutil.move(os.path.join(src, child), dst)

    def unpack_archive(self, filename, extract_dir, format):
        # type: (str, str, str) -> None
        """copy of python3's `shutil.unpack_archive`"""
        if format == "zip":
            if not zipfile.is_zipfile(filename):
                raise OSError("%s is not a zip file" % filename)
            zip = zipfile.ZipFile(filename)
            try:
                for info in zip.infolist():
                    name = info.filename
                    if name.startswith("/") or ".." in name:
                        continue
                    targetpath = os.path.join(extract_dir, *name.split("/"))
                    if not targetpath:
                        continue
                    dirname = os.path.dirname(targetpath)
                    if not os.path.isdir(dirname):
                        os.makedirs(dirname)
                    if not name.endswith("/"):
                        with zip.open(name, "r") as source, open(targetpath, "wb") as target:
                            shutil.copyfileobj(source, target)
            finally:
                zip.close()
        elif format == "tar":
            try:
                tarobj = tarfile.open(filename)
            except tarfile.TarError:
                raise OSError("%s is not a compressed or uncompressed tar file" % filename)
            try:
                tarobj.extractall(extract_dir)
            finally:
                tarobj.close()
        else:
            raise ValueError("Unknown unpack format '{0}'".format(format))


class RayPyBuildExtension(BuildExtension):
    def finalize_options(self):
        # type: () -> None
        BuildExtension.finalize_options(self)
        if not os.path.isdir(RAYLIB_DIR):
            self.run_command("download_deps")


if __name__ == "__main__":
    long_description_content_type, long_description = get_long_description()

    include_dirs = [os.path.join(RAYLIB_DIR, "include")]  # type: list[str]
    library_dirs = [os.path.join(RAYLIB_DIR, "lib")]  # type: list[str]
    libraries = []  # type: list[str]
    extra_objects = []  # type: list[str]
    if "win" in PLATFORM or "mingw" in PLATFORM:
        libraries.extend(["raylib", "user32", "gdi32", "winmm", "shell32"])
    else:
        extra_objects.append(os.path.join(RAYLIB_DIR, "lib", "libraylib.a"))

    try:
        setup(
            name="ray.py",
            version="0.0.1",
            description="CPython native bindings for Raylib",
            long_description=long_description,
            long_description_content_type=long_description_content_type,
            author="Fares Ahmed",
            author_email="fares@duck.com",
            maintainer="Fares Ahmed",
            maintainer_email="fares@duck.com",
            url="https://github.com/faresahmedb/ray.py",
            download_url="https://github.com/faresahmedb/ray.py/releases",
            packages=["raypy"],
            ext_modules=[
                Extension(
                    "raypy.__init__",
                    ["src/raypy.c"],
                    include_dirs=include_dirs,
                    library_dirs=library_dirs,
                    libraries=libraries,
                    extra_objects=extra_objects,
                )
            ],
            classifiers=[
                "Environment :: GPU",
                "Environment :: MacOS X",
                "Environment :: Win32 (MS Windows)",
                "Environment :: X11 Applications",
                "Intended Audience :: Developers",
                "License :: OSI Approved :: zlib/libpng License",
                "Operating System :: MacOS",
                "Operating System :: Microsoft :: Windows",
                "Operating System :: POSIX :: BSD",
                "Operating System :: POSIX :: Linux",
                "Programming Language :: C",
                "Programming Language :: Python",
                "Programming Language :: Python :: 3",
                "Programming Language :: Python :: 3.3",
                "Programming Language :: Python :: 3.4",
                "Programming Language :: Python :: 3.5",
                "Programming Language :: Python :: 3.6",
                "Programming Language :: Python :: 3.7",
                "Programming Language :: Python :: 3.8",
                "Programming Language :: Python :: 3.9",
                "Programming Language :: Python :: 3.10",
                "Programming Language :: Python :: 3.11",
                "Programming Language :: Python :: Implementation :: CPython",
                "Topic :: Games/Entertainment",
                "Topic :: Multimedia",
                "Topic :: Multimedia :: Graphics",
                "Topic :: Multimedia :: Graphics :: 3D Rendering",
                "Typing :: Typed",
            ],
            license="zlib/libpng",
            keywords=["raylib", "graphics", "glfw", "opengl"],
            platforms=["Darwin", "Linux", "Windows"],
            cmdclass={
                "download_deps": DownloadDependencies,
                "build_ext": RayPyBuildExtension,
            },
            package_data={"raypy": ["*.pyi", "py.typed"]},
            include_package_data=True,
        )
    except FetchError as exc:
        sys.stderr.write("errro fetching '%s': %s" % (exc.uri, exc.reason))
