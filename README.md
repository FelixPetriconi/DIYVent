=How to setup=

# The following has only be tested on a recent debian based Linux distribution like Ubuntu or Linuxmint

# Install the following dependencies with sudo apt-get install python3 qt5
# Clone the source code repo with git clone https://github.com/FelixPetriconi/DIYVent.git
# Get all externals with git submodule update --init --recursive
# Setup modm according to the instructions at https://modm.io/guide/installation/. Hereby it is necessary that modm itself is cloned at the same level as the source code repository above.
# Clone modm.io into the same directory as above https://github.com/modm-io/modm.git
# Setup the host part with
** cd DIYVent
** lbuild build (This inits the modm part of the host application)
** cd HostApplication
** qmake ...
** make

# Setup the controller part with
** cd ../controller
** lbuild build
** Attach the controller with an appropriate cable to your computer and configure the access rights to the USB port
** scons program (This compiles the complete code and tries to upload it into the controller)


# Potential problems
* It is important that the very latest version of openocd is used. The version from debian is too old. If the version is too old, then the microcontroller may not be recognized.

