#!/bin/bash

if [[ $CI_JOB_STATUS == 'success' ]]; then
    CI_JOB_STATUS="SUCCESS 🤩🤩🤩"
else
    CI_JOB_STATUS="FAILED 😱😱😱"
fi

TELEGRAM_BOT_TOKEN="5877355693:AAE5kFDQjCDfs3cA8QpPiIvNznKZYh4tBOI"
TELEGRAM_USER_ID="1190955043"
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Author:+$CI_COMMIT_AUTHOR%0A%0AJob name: $CI_JOB_NAME%0A%0AStatus:+$CI_JOB_STATUS%0A%0AProject:+$CI_PROJECT_NAME"

curl -s -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null