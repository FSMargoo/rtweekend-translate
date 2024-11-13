# Ray Tracing in One Weekend 翻译

原作者：Peter Shirley, Trevor David Black, Steve Hollasch

翻译作者：Margoo

作者邮箱：[qiuzhengyu@siggraph.org](mailto:qiuzhengyu@siggraph.org)

## 介绍

Ray Tracing in One Weekend 是有 Peter Shirley 教授编写的入门级别书籍。本书将会引导读者利用几乎一个周末的时间构建一个十分简易的光线追踪图像。 
本书将会从最简单的概念开始介绍起，适合还没有基础的小白阅读。

## 关于本项目

本项目的初衷是在将 Ray Tracing in One Weekend 系列翻译的同时通过 [EasyX](www.easyx.cn) API 进行所有书中示例代码的重写。以便尽可能地降低项目难度、适合新手。

## 前序

Peter Shirley 教授的《Ray Tracing Weekend》系列一直是我极为推崇的入门读物。初次阅读完毕，我便产生了将其翻译的念头。考虑到原书采用的是 PPM 输出格式，而国内教学多用 EasyX，我因此对代码做了适当的 “本土化”处理。同时，我也对原书中的插图进行了重新绘制和翻译，并对某些章节作了调整，以便于后来者的学习。本译文是译者在繁重的课业之余用碎片化的时间所译成的，各种笔误难以文饰，愿各位读者不吝金口，同我一同交流书中的各种纰漏。对于阅读本译本所需要的知识（如基本的向量几何），译者假设读者已经熟悉了如何使用 EasyX 并且已经配置好了相关的环境，本译文不再赘述相关环境的配置等问题。


## 中文翻译说明

您所正在阅读的是中文翻译版本号为 $202477UF$ 的译本（译自英文原本 $VERSION$ $4.0.0-ALPHA.1$, $2023-08-06$）。该版本将本译本由 $\LaTeX$ 重写并加入了作者提供的补充阅读章节，与此同时对部分翻译内容调整。此处不对具体调整做出赘述。

本书中所有章节开头的文章引用内容属译者自行添加。原书中不存在章 节的引用。译者对本译本中的所有翻译的内容、代码负责。由于译者平日学业繁忙，对于原书的版本翻译更近可能会略慢。邮件回复的速度也可能不尽如人意，恳求各位谅解。

本书的扩展阅读均为从原书的百科界面中摘抄的。

## 鸣谢

- 感谢一位名为网名为 $ZhiYi$ 的朋友帮助指出了书中代码的一处低级错误。
- 感谢 $VoidMatrix$ 为本书英文名词翻译提供指导。
- 感谢 $\rho V_0$ 学长对我的没救的英语提供指导。
- 感谢 $Peter$ $Shirley$ 教授及本书其他联合作者对我的翻译工作的认可。

此处应当事人要求（或其他原因）只能留下网名。

## 阅读本书的前置知识要求

以下内容摘自本翻译本前文：

> 在本文中，假设你已经对一些线性代数内容（例如向量，点乘，向量加法）
熟悉，如果你并不清楚这些内容，不如先做点复习，或者先从头开始学起，线上的学习方式，我推荐 Morgan McGuire 的 Graphics Codex7，如果你想要阅
读书本的话，我推荐 Peter Shirley 和 Steve Marschner 的 Fundamentals of
Computer Graphics 或者是 J.D. Foley 和 Adny Van Dam 的 Fundamentals
of Interactive Computer Graphics。

## 本译本所用编程环境

翻译本书时，作者使用的开发环境是 $CLion$ $Nova$（$2024.1$ $EAP$），其 IDE 中自带了一个控制
台以供输出，若读者使用了其他未自带控制台的 IDE 可能无法看到控制台输出（这是因
为 EasyX 默认会关闭控制台），若读者有需要，可以在 Device 类中将 initgraph 改写为
“*initgraph(Width, Height, EW_SHOWCONSOLE)*”。



![](./readme/result.jpg)


