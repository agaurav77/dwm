/*
 * Copyright (C) 2014,2015 levi0x0 with enhancements by ProgrammerNerd
 * 
 * barM (bar_monitor or BarMonitor) is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 *  This is a new version of bar monitor, even less lines of code more effective.
 *
 *  Read main() to configure your new status Bar.
 *
 *  compile: gcc -o barM barM.c -O2 -s -lX11
 *  
 *  mv barM /usr/local/bin/
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <X11/Xlib.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

/*
 *  Put this in your .xinitrc file: 
 *
 *  barM&
 *  
 */

#define VERSION "0.12"
#define TIME_FORMAT "\uf017 %I:%M %p  \uf073 %d %b "
#define MAXSTR  1024

static const char * date(void);
static const char * getuname(void);
static const char * ram(void);
static const char * battery(void);
static void XSetRoot(const char *name);
/*Append here your functions.*/
static const char*(*const functab[])(void)={
        ram,date,battery
};

int main(void){
        char status[MAXSTR];
        /* It is foolish to repeatedly update uname. */
        int ret;
        {struct utsname u;
        if(uname(&u)){
                perror("uname failed");
                return 1;
        }}
        //ret=snprintf(status,sizeof(status),"(%s %s %s) ",u.sysname,u.nodename,u.release);}
        char*off=status+ret;
        if(off>=(status+MAXSTR)){
                XSetRoot(status);
                return 1;/*This should not happen*/
        }
        for(;;){
                int left=sizeof(status)-ret,i;
                char*sta=off;
                for(i = 0; i<sizeof(functab)/sizeof(functab[0]); ++i ) {
                        int ret=snprintf(sta,left,"%s ",functab[i]());
                        sta+=ret;
                        left-=ret;
                        if(sta>=(status+MAXSTR))/*When snprintf has to resort to truncating a string it will return the length as if it were not truncated.*/
                                break;
                }
                XSetRoot(status);
                sleep(1);
        }
        return 0;
}

/* Returns the date*/
static const char * date(void){
        static char date[MAXSTR];
        time_t now = time(0);

        strftime(date, MAXSTR, TIME_FORMAT, localtime(&now));
        return date;
}

static const char * battery(void){
  FILE *status = fopen("/sys/class/power_supply/BAT1/status", "r");
  FILE *capacity = fopen("/sys/class/power_supply/BAT1/capacity", "r");
  char buff1[256], buff2[256];
  static char buff3[256];
  int idx = 0, num = 0;
  fread(buff1, 1, 256, status);
  while (1) {
    char ch = fgetc(capacity);
    if (ch && '0' <= ch && ch <= '9') {
      buff2[idx++] = ch;
      num = num*10+(ch-'0');
    } else {
      break;
    }
  }
  // decide the icon
  //char icon[2];
  //if (num == 100) strcpy(icon, "\uf240");
  //else if (num >= 75) strcpy(icon, "\uf241");
  //else if (num >= 50) strcpy(icon, "\uf242");
  //else if (num >= 25) strcpy(icon, "\uf243");
  //else strcpy(icon, "\uf244");
  buff2[idx] = '\0';
  if (buff1[0] == 'C') {
    snprintf(buff3, sizeof(buff3), "\uf0e7 %s%%", buff2);
  } else {
    snprintf(buff3, sizeof(buff3), "\ue220 %s%%", buff2);
    //snprintf(buff3, sizeof(buff3), "%s %s%%", icon, buff2);
  }
  return buff3;
}

/* Returns a string that contains the amount of free and available ram in megabytes*/
static const char * ram(void){
  FILE *meminfo = fopen("/proc/meminfo", "r");
  int totalMemory = 0, aMem = 0;
  float div;
  char buff[256];
  while(fgets(buff, sizeof(buff), meminfo)) {
    int ramKB;
    if (sscanf(buff, "MemAvailable: %d kB", &aMem) == 1) aMem /= 1024;
    if (sscanf(buff, "MemTotal: %d kB", &totalMemory) == 1) totalMemory /= 1024;
  }
  static char ram[MAXSTR];
  if (totalMemory-aMem < 1024) {
    //snprintf(ram, sizeof(ram), "\uf200 %dM used of %.2fG -", (totalMemory-aMem), totalMemory/1024.0);
    snprintf(ram, sizeof(ram), "\uf200 %dM ", (totalMemory-aMem));
  } else {
    div = (totalMemory-aMem)/1024.0;
    //snprintf(ram, sizeof(ram), "\uf200 %.2fG used of %.2fG -", div, totalMemory/1024.0);
    snprintf(ram, sizeof(ram), "\uf200 %.2fG ", div);
  }
  return ram;
}

static void XSetRoot(const char *name){
        Display *display;

        if (( display = XOpenDisplay(0x0)) == NULL ) {
                fprintf(stderr, "[barM] cannot open display!\n");
                exit(1);
        }

        XStoreName(display, DefaultRootWindow(display), name);
        XSync(display, 0);

        XCloseDisplay(display);
}
