
#!/bin/sh
source=/home/ubuntu/datas/datas.json

if test -f  "$1"; then
        dt=$(date  "+%Y%m%d-%H%M%S%s")
        mv "$1" /home/ubuntu/success/"$dt"
fi
exit 0
