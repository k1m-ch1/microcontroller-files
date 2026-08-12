Import("env")

env.Replace(
    UPLOADER="st-flash",
    UPLOADCMD='$UPLOADER write $SOURCE 0x08000000'
)
