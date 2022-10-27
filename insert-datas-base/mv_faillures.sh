
#!/bin/sh
source=/home/mrzk/datas/datas.json

if test -f  "$1"; then
        dt=$(date  "+%Y%m%d-%H%M%S%s")
        mv "$1" /home/mrzk/faillures/"$dt"
fi
exit 0
