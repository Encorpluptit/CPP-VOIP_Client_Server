![Build](https://github.com/Encorpluptit/CPP_babel_2020/workflows/Build/badge.svg)
[![codecov](https://codecov.io/gh/Encorpluptit/CPP_babel_2020/branch/master/graph/badge.svg?token=ttl8s3om9V)](https://codecov.io/gh/Encorpluptit/CPP_babel_2020)

- [CPP_babel_2020](#cpp-babel-2020)
  * [How to Use](#how-to-use)
    + [Client](#client)
    + [Server](#server)
    + [Protocol](#protocol)
    + [UML](#uml)
  * [Install instruction](#install-instruction)
    + [Install conan](#install-conan-------warning--------pip3-required-)
    + [Add conan repositories for libraries.](#add-conan-repositories-for-libraries)
    + [Install dependencies (can take several minutes)](#install-dependencies--can-take-several-minutes-)
  * [Build Rules](#build-rules)
    + [`make` | `make babel`](#-make-----make-babel-)
    + [`make server`](#-make-server-)
    + [`make client`](#-make-client-)
    + [`make clean`](#-make-clean-)
    + [`make fclean`](#-make-fclean-)
    + [`make re`](#-make-re-)

# CPP_babel_2020
[Epitech Project] C++ project in a client/server architecture voice over IP application, similar to Skype or TeamSpeak.

---
##  How to Use

* ### Client

* ### Server

* ### [Protocol](Doc/Protocol.md "Full protocol documentation")

* ### UML


---
## Install instruction
* ### Install [conan](https://conan.io/ "Conan's Homepage") ( **[ Warning !! ]** pip3 required)
        
        pip install conan

* ### Add conan repositories for libraries.

        conan remote add tech-repo https://api.bintray.com/conan/epitech/public-conan
        conan remote add public-repo https://api.bintray.com/conan/bincrafters/public-conan
        
    Check with this command if repositories were indeed added.
    
    ![alt text][logo]
    
    [logo]: .github/assets/conan_remotes_list.png "Image in .github/assets"
    
* ### Install dependencies (can take several minutes)

        mkdir -p build && cd build && conan install .. 

    or if that doesn't work

        mkdir -p build && cd build && conan install .. --build=missing
        
        or
        
        make mouli-install


---

## Build Rules 
(CMakeList.txt wrapped by Makefile)
* ### `make` | `make babel`
    Build **babel_client** and **babel_server** binaries.
    
    (create **.babel_server_build** and **.babel_client_build** folders)
    
    
* ### `make server`
    Build **babel_server** binary.
    
    (create **.babel_server_build** folder)
    
    
* ### `make client`
    Build **babel_client** binary.
    
    (create **.babel_client_build** folder)


* ### `make mouli-install`
    Install conan dependencies and build them.
    
    (create **build** folder)


* ### `make mouli`
    Install conan dependencies, build them, make build tree and compile project.
    
    (create **build** folder)


* ### `make clean`
    Remove **.babel_server_build** and **.babel_client_build** folders.

    
* ### `make fclean`
    Remove **babel_client** and **babel_client** binaries and call clen rule.
    
    
* ### `make re`
    Call fclean and make

