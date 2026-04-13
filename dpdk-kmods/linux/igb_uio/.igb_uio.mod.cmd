savedcmd_igb_uio.mod := printf '%s\n'   igb_uio.o | awk '!x[$$0]++ { print("./"$$0) }' > igb_uio.mod
