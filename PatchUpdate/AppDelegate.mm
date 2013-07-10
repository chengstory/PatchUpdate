//
//  AppDelegate.m
//  PatchUpdate
//
//  Created by 张成 on 13-7-10.
//  Copyright (c) 2013年 张成. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
}

-(IBAction)update:(id)sender{
    NSFileManager *fileManager = [NSFileManager defaultManager];

    //获取本地resources目录
    NSString *atPath = [[NSBundle mainBundle] pathForResource:@"Resources" ofType:nil];

    NSError *error = nil;
    NSAlert *alert = nil;
    do
    {
        //路径为空
        NSString *toPatch = self.textField.stringValue;
        if (toPatch == nil || [toPatch isEqualToString:@""])
        {
            error = [NSError errorWithDomain:@"请指定路径" code:0 userInfo:nil];
            alert = [NSAlert alertWithError:error];
            [alert runModal];
            return;
        }
    
        //获取子目录
        NSArray  *array =  [fileManager subpathsOfDirectoryAtPath:atPath error:&error];
        if (error != nil)
        {
            alert = [NSAlert alertWithError:error];
            [alert runModal];
            return;
        }
        
        for (NSString *subPatch in array)
        {
            error = nil;
            NSDictionary *dic = [fileManager attributesOfItemAtPath:[NSString stringWithFormat:@"%@/%@", atPath, subPatch] error:&error];
            if (error != nil)
            {
                alert = [NSAlert alertWithError:error];
                [alert runModal];
                return;
            }
            
            //如果不是目录的话
            id value = [dic objectForKey:@"NSFileType"];
            if(value != NSFileTypeDirectory)
            {
                NSString *toPatchFinal = [NSString stringWithFormat:@"%@/%@", toPatch, subPatch];
                if ([fileManager fileExistsAtPath:toPatchFinal])
                {
                    //移除目标目录的文件
                    [fileManager removeItemAtPath:toPatchFinal error:&error];
                    if (error != nil)
                    {
                        alert = [NSAlert alertWithError:error];
                        [alert runModal];
                        return;
                    }
                }
            
                //从补丁目录拷贝到目标目录
                NSString *fromPatchFinal = [NSString stringWithFormat:@"%@/%@", atPath, subPatch];
                [fileManager copyItemAtPath:fromPatchFinal toPath:toPatchFinal error:&error];
                if (error != nil)
                {
                    NSAlert *alert = [NSAlert alertWithError:error];
                    [alert runModal];
                    return;
                }
                
            }
            else
            {
                NSString *toPatchFinal = [NSString stringWithFormat:@"%@/%@", toPatch, subPatch];
                [fileManager createDirectoryAtPath:toPatchFinal withIntermediateDirectories:YES attributes:nil error:&error];
                
                if (error != nil)
                {
                    NSAlert *alert = [NSAlert alertWithError:error];
                    [alert runModal];
                    return;
                }
            }
        }
    
    }while (0);
        
    alert = [NSAlert alertWithMessageText:@"升级成功" defaultButton:@"确定" alternateButton:nil otherButton:nil informativeTextWithFormat:@""];
    [alert runModal];
}

@end
