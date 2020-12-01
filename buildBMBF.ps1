# Builds a .zip file for loading with BMBF
& $PSScriptRoot/build.ps1

if ($?) {
    Compress-Archive -Path "./libs/arm64-v8a/libunhealthyandunsafe.so", "./libs/arm64-v8a/libbeatsaber-hook_0_8_4.so", "./cover.jpg", "./bmbfmod.json" -DestinationPath "./UnhealthyAndUnsafe.zip" -Update
}
