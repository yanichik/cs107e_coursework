# (c) Stanford University 2018
# Written by Mark Miller, 2/15/2018
# Shell script to put the mac_toolchain rpi-install in the right place.
# This assumes git has been pulled.

rpi_install_source="cs107e.github.io/guides/mac_toolchain/rpi-install.py"

if [ -z "$1" ]; then
  rpi_install_dest="/home/rpi/bin/rpi-install.py"
else
  rpi_install_dest="$1";
fi

if [ ! -f "$rpi_install_source" ]; then
  echo "rpi-install was not found. Are you running this script from the same directory that cs107e.github.io is in?" 
  exit 1
fi

cp $rpi_install_source $rpi_install_dest
if [ $? = "1" ]; then
  echo "Copy couldn't work... are you running as root?"
  exit 1
fi
chown root $rpi_install_dest
chmod 755 $rpi_install_dest

