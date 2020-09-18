from conans import ConanFile, CMake, tools
from os import system

class Babel(ConanFile):
    settings = {"os": None, "build_type": None, "compiler": None, "arch": ["x86_64"]}

    build_policy = "always"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = "shared=False", "fPIC=True"
    generators = "cmake", "cmake_find_package", "cmake_paths", "gcc"
    requires = "sqlite_orm/1.5@bincrafters/stable",             \
        "zlib/1.2.11@conan/stable",                             \
        "bzip2/1.0.8@conan/stable",                             \
        "boost/1.71.0@conan/stable",                            \
        "qt/5.14.2@bincrafters/stable",                         \
        "sqlite3/3.32.3@_/_",                                   \
        "portaudio/v190600.20161030@bincrafters/stable",        \
        "opus/1.3.1@bincrafters/stable"
    # "qt/5.15.1@bincrafters/stable",                         \


    def configure(self):
        self.system_requirements()
        # self.options["Qt"].shared = True
        # if self.settings.os == "Windows":
        #     self.options["portaudio"].shared = True

    def system_requirements(self):
        if tools.os_info.is_linux and self.settings.os == "Linux":
            packages = []
            package_tool = tools.SystemPackageTool(conanfile=self, default_mode="enabled")
            if tools.os_info.with_apt:
                packages = [
                    "xorg-dev",
                    "libx11-xcb-dev",
                    "libxcb-render0-dev",
                    "libxcb-render-util0-dev",
                    "libxcb-xkb-dev",
                    "libxcb-icccm4-dev",
                    "libxcb-image0-dev",
                    "libxcb-keysyms1-dev",
                    "libxcb-randr0-dev",
                    "libxcb-shape0-dev",
                    "libxcb-sync-dev",
                    "libxcb-xfixes0-dev",
                    "libxcb-xinerama0-dev"
                ]
            elif tools.os_info.with_dnf:
                # conan profile update settings.compiler.libcxx=libstdc++11 default
                packages = [
                    "xorg-x11-server-devel",
                    "libxcb-devel",
                    "libXaw-devel",
                    "libXcomposite-devel",
                    "libXcursor-devel",
                    "libXdmcp-devel",
                    "libXtst-devel",
                    "libXinerama-devel",
                    "xorg-x11-xkb-utils-devel",
                    "libXrandr-devel",
                    "libXres-devel",
                    "libXScrnSaver-devel",
                    "libXvMC-devel",
                    "xorg-x11-xtrans-devel",
                    "xcb-util-wm-devel",
                    "xcb-util-keysyms-devel",
                    "xcb-util-renderutil-devel",
                    "libXdamage-devel",
                    "libXv-devel",
                    "xkeyboard-config-devel"
                ]
            elif tools.os_info.with_yum:
                packages = [
                    "xorg-x11-server-devel",
                    "libXaw-devel.x86_64"
                ]
            elif tools.os_info.with_pacman:
                packages = [
                    "xorg-server-devel",
                ]
            elif tools.os_info.with_zypper:
                packages = ["Xorg-x11-devel"]
            else:
                self.warn("Do not know how to install system requirements for {}.".format(tools.os_info.linux_distro))
            package_tool.install(update=True, packages=" ".join(packages))


    # def imports(self):
    #     self.copy("*.dll", dst="bin", src="bin") # From bin to bin

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        # self.run("cmake --build . %s" % cmake.build_config)
        cmake.build(build_type="missing")