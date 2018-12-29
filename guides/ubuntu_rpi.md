---
layout: page
title: Updating rpi-install on Ubuntu
---

At points during the course we will release fixes and features for the
rpi-install program. We've built a script to help the updating process.

## Instructions
- Pull the most recent `cs107e.github.io` repository.
- Download the updating script from the guide. It is available at [this link.](update_rpi_install.sh)
- Move this script to the same directory that the `cs107e.github.io` repository is in.
```
cs107e_home
├── update_rpi_install.sh <-- like this.
├── assign1
├── assign2
├── ...
├── cs107e.github.io
│   ├── ...
│   ├── cs107e
│   │   ├── etc
│   │   ├── include
│   │   ├── lib
│   │   └── src
│   └── ...
├── lab1
├── lab2
└── ...
```
- Give the downloaded file execute permissions with `chmod a+x update_rpi_install.sh`
- Run the script with `sudo`, like this: `sudo ./update_rpi_install.sh`
- Celebrate success, or complain to Piazza about failure.

