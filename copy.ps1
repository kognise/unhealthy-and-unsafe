& $PSScriptRoot/build.ps1
if ($?) {
    adb push libs/arm64-v8a/libunhealthyandunsafe.so /sdcard/Android/data/com.beatgames.beatsaber/files/mods/libunhealthyandunsafe.so
    if ($?) {
        adb shell am force-stop com.beatgames.beatsaber
        adb shell am start com.beatgames.beatsaber/com.unity3d.player.UnityPlayerActivity
        adb logcat main-modloader:W QuestHook[unhealthyandunsafe`|v0.1.2]:* AndroidRuntime:E *:S > cat.log
    }
}
