/*****************************************************************

                    FiTimestamp by ZTzTopia
                        v0.1.3

*****************************************************************/

#if !defined _samp_included
    #error "Please include a_samp before FiTimestamp"
#endif

#if defined _FiTimestamp_included
    #error "FiTimestamp aleardy included on your gamemodes/filterscripts"
#elseif !defined _FiTimestamp_included
    #define _FiTimestamp_included
#endif

#define SetSeconds(%0) GetTotalTimestampEx(0, 0, 0, 0, 0, %0)
#define SetMiutes(%0)  GetTotalTimestampEx(0, 0, 0, 0, %0, 0)
#define SetHours(%0)   GetTotalTimestampEx(0, 0, 0, %0, 0, 0)
#define SetDays(%0)    GetTotalTimestampEx(0, 0, %0, 0, 0, 0)
#define SetMonths(%0)  GetTotalTimestampEx(0, %0, 0, 0, 0, 0)
#define SetYears(%0)   GetTotalTimestampEx(%0, 0, 0, 0, 0, 0)

new MonthTimes[12][4] = {
    {31, 31, 2678400, 2678400}, // Normal, Leap, Normal Timestamp, Leap Timestamp
    {28, 29, 2419200, 2505600},
    {31, 31, 2678400, 2678400},
    {30, 30, 2592000, 2592000},
    {31, 31, 2678400, 2678400},
    {30, 30, 2592000, 2592000},
    {31, 31, 2678400, 2678400},
    {31, 31, 2678400, 2678400},
    {30, 30, 2592000, 2592000},
    {31, 31, 2678400, 2678400},
    {30, 30, 2592000, 2592000},
    {31, 31, 2678400, 2678400}
};
 
stock IsLeapYear(year)
{ 
    if((365 + (!(year & 0x03) ? 1 : 0)) == 366) return 1;
    else return 0;
}

/*
    native GetDate(HourGMT = 0, MinuteGMT = 0);
*/
stock GetDate(HourGMT = 0, MinuteGMT = 0)
{
    new string[128], MonthStr[32], month, day, year, hour, minute, second;
    gettime(hour, minute, second);
    getdate(year, month, day);
    hour += HourGMT;
    minute += MinuteGMT;
    switch(month)
    {
        case 1:  MonthStr = "January";
        case 2:  MonthStr = "February";
        case 3:  MonthStr = "March";
        case 4:  MonthStr = "April";
        case 5:  MonthStr = "May";
        case 6:  MonthStr = "June";
        case 7:  MonthStr = "July";
        case 8:  MonthStr = "August";
        case 9:  MonthStr = "September";
        case 10: MonthStr = "October";
        case 11: MonthStr = "November";
        case 12: MonthStr = "December";
    }
    format(string, sizeof(string), "%s %d %d, %02d:%02d:%02d", MonthStr, day, year, hour, minute, second);
    return string;
}

/*
    native GetDateEx(year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, HourGMT = 0, MinuteGMT = 0);
*/
stock GetDateEx(year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, HourGMT = 0, MinuteGMT = 0)
{
    new string[128], MonthStr[32];
    hour += HourGMT;
    minute += MinuteGMT;
    switch(month)
    {
        case 1:  MonthStr = "January";
        case 2:  MonthStr = "February";
        case 3:  MonthStr = "March";
        case 4:  MonthStr = "April";
        case 5:  MonthStr = "May";
        case 6:  MonthStr = "June";
        case 7:  MonthStr = "July";
        case 8:  MonthStr = "August";
        case 9:  MonthStr = "September";
        case 10: MonthStr = "October";
        case 11: MonthStr = "November";
        case 12: MonthStr = "December";
        default: MonthStr = "Unknown";
    }
    format(string, sizeof(string), "%s %d %d, %02d:%02d:%02d", MonthStr, day, year, hour, minute, second);
    return string;
}

/*
    native TimestampToDate(Timestamp, &year, &month, &day, &hour, &minute, &second, HourGMT = 0, MinuteGMT = 0);
*/
stock TimestampToDate(Timestamp, &year, &month, &day, &hour, &minute, &second, HourGMT = 0, MinuteGMT = 0)
{
    new days, seconds;
    for(year = 1970; ; year++)
    {
        seconds = (365 + (!(year & 0x03) ? 1 : 0)) * 86400;
        if(seconds > Timestamp)
            break;
        Timestamp -= seconds;
    }
    for(month = 1; ; month++)
    {
        seconds = MonthTimes[month - 1][IsLeapYear(year) + 2];
        if(seconds > Timestamp)
            break;
        Timestamp -= seconds;
    }
    for(day = 1; Timestamp >= 86400; day++)
    {
        days = MonthTimes[month - 1][IsLeapYear(year)];
        if(day >= days)
        {
            day = 0;
            month++;
        }
        Timestamp -= 86400;
    }
    for(hour = HourGMT; Timestamp >= 3600; hour++)
    {
        if(hour >= 24)
        {
            hour = 0;
            day++;
        }
        Timestamp -= 3600;
    }
    if(hour >= 24)
    {
        hour = 0;
        day++;
    }
    for(minute = MinuteGMT; Timestamp >= 60; minute++)
    {
        if(minute >= 60)
        {
            minute = 0;
            hour++;
        }
        Timestamp -= 60;
    }
    if(minute >= 60)
    {
        minute = 0;
        hour++;
    }
    if(second >= 60)
    {
        second = 0;
        minute++;
    }
    second = Timestamp;
    return 1;
}

/*
    native GetTimestampEx(year = 0, month = 0, day, hour = 0, minute = 0, second = 0, HourGMT = 0, MinuteGMT = 0);
*/
stock GetTimestampEx(year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, HourGMT = 0, MinuteGMT = 0)
{
    new Timestamp;
    if(month == 12) month--;
    for(new y = 1970; y < year; y++)
        Timestamp += (365 + (!(y & 0x03) ? 1 : 0)) * 86400;
    for(new m = 1; m < month; m++)
        Timestamp += MonthTimes[m][IsLeapYear(year) + 2];

    if(IsLeapYear(year)) Timestamp += 86400;
    else Timestamp += 2 * 86400;

    Timestamp += day * 86400;
    Timestamp += HourGMT + hour * 3600;
    Timestamp += MinuteGMT + minute * 60;
    Timestamp += second;
    return Timestamp;
}

/*
    native GetTotalTimestampEx(year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, HourGMT = 0, MinuteGMT = 0)
*/
stock GetTotalTimestampEx(year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, HourGMT = 0, MinuteGMT = 0)
{
    new TimeNow = gettime(), date[6];
    TimestampToDate(TimeNow, date[0], date[1], date[2], date[3], date[4], date[5]);
    if(date[1] == 12) date[1]--;
    TimeNow += year * ((!(date[0] & 0x03) ? 366 : 365) * 86400);
    TimeNow += month * MonthTimes[date[1]][IsLeapYear(year) + 2];

    if(IsLeapYear(year)) TimeNow += 86400;
    else TimeNow += 2 * 86400;

    TimeNow += day * 86400;
    TimeNow += HourGMT + hour * 3600;
    TimeNow += MinuteGMT + minute * 60;
    TimeNow += second;
    return TimeNow;
}
