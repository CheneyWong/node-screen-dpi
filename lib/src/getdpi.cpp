/*
MIT License

Copyright (c) 2020-2021 Anthony Beaumont

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <napi.h>
#include <math.h>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif
#if defined(__linux) || defined(__unix) || defined(__posix)
#include <X11/Xlib.h>
#endif
#include <iostream>

Napi::Object GetScreen(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::Object screen = Napi::Object::New(env);
#if defined(_WIN32) || defined(_WIN64)
	HDC hdc = GetDC(NULL); // 得到屏幕DC
	// 在electron中 缩放后分辨率获取失败获取到还是原始分辨率
	int pixWidth = GetDeviceCaps(hdc, HORZRES);			//屏幕宽度实际尺寸mm
	int pixHeight = GetDeviceCaps(hdc, VERTRES);		//屏幕高度实际尺寸mm
	int dhcWidth = GetDeviceCaps(hdc, HORZSIZE);		//屏幕X分辨率
	int hdcHeight = GetDeviceCaps(hdc, VERTSIZE);		//屏幕Y分辨率
	int deskW = GetDeviceCaps(hdc, DESKTOPHORZRES); //屏幕X分辨率未缩放时
	int deskH = GetDeviceCaps(hdc, DESKTOPVERTRES); //屏幕Y分辨率未缩放时
	double dScrLeng = sqrt((double)(dhcWidth * dhcWidth + hdcHeight * hdcHeight));
	int dpi = (int)(sqrt(deskW * deskW + deskH * deskH) / (dScrLeng / 25.4));
	screen.Set("dpi", dpi);
	screen.Set("width", pixWidth);
	screen.Set("height", pixHeight);
	screen.Set("widthDC", dhcWidth);
	screen.Set("heightDC", hdcHeight);
	// 未缩放的分辨率
    screen.Set("w", deskW);
    screen.Set("h", deskH);
#endif
#if defined(__linux) || defined(__unix) || defined(__posix)
	Display *display;
	// Screen *screenx;
	display = XOpenDisplay(NULL);
	int screen_num = DefaultScreen(display);
	// screenx = XScreenOfDisplay(display, screen_num);
	int wmm = DisplayWidthMM(display, screen_num);
	int hmm = DisplayHeightMM(display, screen_num);
	int w = DisplayWidth(display, screen_num);
	int h = DisplayHeight(display, screen_num);
	double dScrLeng = sqrt((double)(wmm * wmm + hmm * hmm));
	int dpi = (int)(sqrt(w * w + h * h) / (dScrLeng / 25.4));
	screen.Set("widthDC", wmm);
	screen.Set("heightDC", hmm);
	screen.Set("width", w);
	screen.Set("height", h);
	screen.Set("dpi", dpi);
    // 未缩放的分辨率
    screen.Set("w", deskW);
    screen.Set("h", deskH);
#endif
	return screen;
}

/* NAPI Initialize add-on*/

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	exports.Set("GetScreen", Napi::Function::New(env, GetScreen));
	return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)