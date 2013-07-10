//
//  AppDelegate.h
//  PatchUpdate
//
//  Created by 张成 on 13-7-10.
//  Copyright (c) 2013年 张成. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;

@property (assign) IBOutlet NSTextField *textField;

-(IBAction)update:(id)sender;

@end
