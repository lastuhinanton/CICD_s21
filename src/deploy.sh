#!/bin/bash

REMOTE_USER="root"
REMOTE_HOST="10.20.0.1"
REMOTE_DIR="/usr/local/bin"
LOCAL_DIR_1="./src/cat/s21_cat"
LOCAL_DIR_2="./src/grep/s21_grep"

scp $LOCAL_DIR_1 $REMOTE_USER@$REMOTE_HOST:$REMOTE_DIR
scp $LOCAL_DIR_2 $REMOTE_USER@$REMOTE_HOST:$REMOTE_DIR