/*
 Copyright (C) 2013 MoSync AB

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License,
 version 2, as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA 02110-1301, USA.
 */

#import <Foundation/Foundation.h>
#include <helpers/cpp_defs.h>

// C
void MoSyncUIUtils_ShowMessageBox(const char *title, const char *msg, bool kill);
void MoSyncUIUtils_ShowAlert(const char* title, const char* message, const char* button1, const char* button2, const char* button3);
void MoSyncUIUtils_ShowTextBox(const wchar* title, const wchar* inText, wchar* outText, int maxSize, int constraints);

void MoSyncUIUtils_ShowImagePicker();
void MoSyncUIUtils_ShowImagePicker(int returnType);

// Obj
@interface MoSyncUIUtils : NSObject

+(void) showMessageBox:(NSString*)msg
             withTitle:(NSString*)title
            shouldKill:(bool)kill;

+(void) showAlert:(NSString*)msg
        withTitle:(NSString*)title
     button1Title:(NSString*)buton1
     button2Title:(NSString*)buton2
     button3Title:(NSString*)buton3;

+(void) showTextBox:(NSString*)title
         withInText:(NSString*)inText
			outText:(wchar*)outText
			maxSize:(int)maxSize
     andConstraints:(int)constraints;

@end
