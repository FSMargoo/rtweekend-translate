/*
 * Copyright (c) 2023~Now Margoo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * \file device.h
 * \brief 封装了有关绘图设备相关的操作
 */

#pragma once

#include <graphics.h>
#include <iostream>

/**
 * \brief 绘图设备的封装类
 */
class Device {
public:
	Device(const int& WWidth, const int& WHeight)
		: Width(WWidth), Height(WHeight), MaximumPixel(Width * Height) {
		Handle = initgraph(Width, Height);
		if (Handle != nullptr) {
			Buffer = GetImageBuffer();

			BeginBatchDraw();
		} else {
			std::clog << "\rDevice Creating Failure : No widget has been created."
					  << std::flush;

			exit(-1);
		}
	}

public:
	DWORD& At(const size_t& X, const size_t& Y) const {
		/* Fixed in 2024/4/7
		 * Original Code : Y * Height + X >= MaximumPixel
		 * Thanks to Zhi Yi
		 */
		if (Y * Width + X >= MaximumPixel) {
			std::clog << "\rDevice Failure : Subscript out of range." << std::flush;
		}

		return Buffer[Y * Width + X];
	}

	static void Flush() {
		FlushBatchDraw();
	}

private:
	HWND   Handle;
	DWORD* Buffer;
	int	   Width;
	int	   Height;
	int	   MaximumPixel;
};
