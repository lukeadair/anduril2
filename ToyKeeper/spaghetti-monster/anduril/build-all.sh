#!/bin/sh

UI=anduril

date '+#define VERSION_NUMBER "%Y%m%d"' > version.h

PASS=0
FAIL=0
PASSED=''
FAILED=''

for TARGET in cfg-*.h ; do

  # friendly name for this build
  NAME=$(echo "$TARGET" | perl -ne '/cfg-(.*).h/ && print "$1\n";')
  echo "===== $NAME ====="

  # figure out MCU type
  ATTINY=$(grep 'ATTINY:' $TARGET | awk '{ print $3 }')
  if [ -z "$ATTINY" ]; then ATTINY=85 ; fi

  # try to compile
  echo ../../../bin/build.sh $ATTINY "$UI" "-DCONFIGFILE=${TARGET}"
  ../../../bin/build.sh $ATTINY "$UI" "-DCONFIGFILE=${TARGET}"

  # track result, and rename compiled files
  if [ 0 = $? ] ; then
    mv -f "$UI".hex "$UI".$NAME.hex
    PASS=$(($PASS + 1))
    PASSED="$PASSED $NAME"
  else
    echo "ERROR: build failed"
    FAIL=$(($FAIL + 1))
    FAILED="$FAILED $NAME"
  fi

done

# summary
echo "===== $PASS builds succeeded, $FAIL failed ====="
#echo "PASS: $PASSED"
if [ 0 != $FAIL ]; then
  echo "FAIL:$FAILED"
fi
