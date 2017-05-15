#include "jtalk.h"

int main()
{
	auto jtalk = new JTalk();
	if (jtalk)
	{
		printf("�g�p�\�����t�@�C��:\n");
		for (auto voice : jtalk->voices)
		{
			printf("%s\n", voice->path);
		}
		printf("\n");
		jtalk->SetSpeed(2.0);
		jtalk->SetVoice(u8"mei_normal");
		jtalk->SpeakAsync_u16(u"\u3053\u3093\u306b\u3061\u306f");
		jtalk->WaitUntilDone();
		jtalk->SetSpeed(1.0);
		jtalk->SpeakAsync(u8"UTF-8�ł��B");
		jtalk->Wait(1000);
		jtalk->SpeakAsync(u8"���j�R�[�h�ŁA����ɂ���");
		jtalk->WaitUntilDone();
		getchar();
		delete jtalk;
	}
}

