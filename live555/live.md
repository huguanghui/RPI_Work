[TOC]

---
# live555的Demon分析
## testH264VideoStreamer.cpp分析
- *创建Usage environment*
- *为RTP和RTCP创建groupsocks*
- *从RTP的groupsocks中创建一个H264视频RTP*
- *为RTPSink创建或开始一个“RTCP instance”*
- *开始Streaming*

### TaskScheduler类
