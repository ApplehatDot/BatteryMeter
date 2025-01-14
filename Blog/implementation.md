# Implementing functions and searching through WinAPI Docs

This Blog (a.k.a. _this file_) will briefly explain how were battery indicators (structs and functions) used, and how _i thought to implement, and how i actually implemented a function_
_____
### Book of contents - Useful Links to WinAPI docs:
_referred by two last directories in the link._<br>
- SYSTEM_POWER_STATUS structure and it's results - [winbase/ns-winbase-system_power_status](https://learn.microsoft.com/en-us/windows/win32/api/winbase/ns-winbase-system_power_status)
- GetSystemPowerStatus function - [winbase/nf-winbase-getsystempowerstatus](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getsystempowerstatus)
- MicrosoftDocs' repository in Power Section - [desktop-src/Power](https://github.com/MicrosoftDocs/win32/tree/docs/desktop-src/Power)
____
## 1. Private testing
Before i try to implement anything, i always tried it by making an example executable and testing/playing around a feature. These source codes _aren't so advanced and all that_. Here's the example source code:

```c
#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

void PrintPowerStatus() {
    SYSTEM_POWER_STATUS sps;
	
	char LifeTimeStat_str[50];
	char FullLT_str[100];
	
	long LifeTimeStat_HOURS = sps.BatteryLifeTime / 3600;
	if (LifeTimeStat_HOURS > 300 || sps.ACLineStatus == true){
		strcpy(LifeTimeStat_str, "NO READING - Charger is connected");
	} else {
        snprintf(LifeTimeStat_str, sizeof(LifeTimeStat_str), "%ld hours", LifeTimeStat_HOURS);
    }
	
	long FullLT_HOURS = sps.BatteryFullLifeTime / 3600;
	if(sps.BatteryFullLifeTime = -1){
		strcpy(FullLT_str, "NOT DEFINED - try fully discharging a battery, it happens when its a new battery.");
	} else {
		snprintf(LifeTimeStat_str, sizeof(LifeTimeStat_str), "%ld hours", FullLT_HOURS);
	}
	
    if (GetSystemPowerStatus(&sps)) {
        printf("AC Line Status: %s\n", sps.ACLineStatus == 0 ? "Offline" : "Online");
        printf("Battery Flag: %u\n", sps.BatteryFlag);
        printf("Battery Life Percent: %u%%\n", sps.BatteryLifePercent);
        printf("Battery Life Time: %s\n", LifeTimeStat_str);
        printf("Battery Full Life Time: %s\n", FullLT_str);
    } else {
        printf("Failed to get power status.\n");
    }
}

int main() {
    PrintPowerStatus();
    return 0;
}
```

This one has some issues with Life Time Battery indicator beside being disconnected, still shows "NO READING - Charger is connected". But it dosen't matter - since it's a playground, dosen't have to work.
