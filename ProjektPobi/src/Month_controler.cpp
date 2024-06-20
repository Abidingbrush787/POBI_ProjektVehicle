#include "../include/Containers/Month_controler.h"

std::string monthToString(int month) {
    switch (month) {
    case 1: return "Jan";
    case 2: return "Feb";
    case 3: return "Mar";
    case 4: return "Apr";
    case 5: return "May";
    case 6: return "Jun";
    case 7: return "Jul";
    case 8: return "Aug";
    case 9: return "Sep";
    case 10: return "Oct";
    case 11: return "Nov";
    case 12: return "Dec";
    default: return "Invalid";
    }
}

int stringToMonth(const std::string& month) {
    if (month == "Jan" || month == "January") return 1;
    if (month == "Feb" || month == "February") return 2;
    if (month == "Mar" || month == "March") return 3;
    if (month == "Apr" || month == "April") return 4;
    if (month == "May") return 5;
    if (month == "Jun" || month == "June") return 6;
    if (month == "Jul" || month == "July") return 7;
    if (month == "Aug" || month == "August") return 8;
    if (month == "Sep" || month == "September") return 9;
    if (month == "Oct" || month == "October") return 10;
    if (month == "Nov" || month == "November") return 11;
    if (month == "Dec" || month == "December") return 12;
    return -1; // Invalid month
}
