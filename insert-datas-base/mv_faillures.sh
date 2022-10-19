
#!/bin/sh
source=/home/ubuntu/datas/datas.json

if test -f  "$source"; then
        dt=$(date  "+%Y%m%d-%H%M%S")
        mv "$source" /home/ubuntu/faillures/"$dt"
fi
exit 0
