# Running

## Script
In order to run `park.sh` you must have a drive configuration up as per: https://github.com/odeke-em/drive#initializing
After initializing the script will only work inside the designated directory and its subdirectories.

To encrypt and upload run:
```
/csproj/park.sh -u USER -k PRIVATE_KEY -s SHARING_KEYBASE_USERNAME upload FILE
```

to decrypt:
```
/csproj/park.sh -d -m META_FILE -k PRIVATE_KEY -u USER decrypt FILE
```

## Cryptographic functions
In order to just run the functions, make sure you have docker and pull jwoos/csuy4783-project2:latest
run it with:

```
docker run -it --rm jwoos/csuy4783-project2:latest
```

This will bring up a bash console. To run encryption run:

```
dotnet bin/Release/netcoreapp1.1/project2.dll -i INPUT_FILE -o OUTPUT_FILE -k PRIVATE_KEY -r SHARING_KEYBASE_USERNAME
```

The r flag has to be repeated for each person you would like to share the file with

To decrypt run:

```
dotnet bin/Release/netcoreapp1.1/project2.dll -i INPUT_FILE -o OUTPUT_FILE -k PRIVATE_KEY -m META_FILE
```
