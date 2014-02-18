#!/bin/sh
FILE=.git/hooks/pre-commit

echo '#/bin/sh' > $FILE
echo 'make MODE=release all' >> $FILE
echo 'exit $?' >> $FILE

chmod 750 $FILE
