/*****************************************************************
** OpenJTalk.TTS
*/
#pragma once
#include "jtalk.h"
#include <msclr/marshal.h>

using namespace System::IO;
using namespace System::Reflection;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace msclr::interop;

namespace Openjtalk {

	/// <summary>
	/// �����t�@�C���f�[�^�̃C���^�[�t�F�C�X
	/// </summary>
	[Guid("75CDB8C8-BF88-47AA-97FA-D88EF80EFEB8")]
	[InterfaceType(ComInterfaceType::InterfaceIsDual)]
	public interface class IVoiceFileData
	{
		property System::String^ Path {System::String^ get(); }
		property System::String^ Name {System::String^ get(); }
	};


	/// <summary>
	/// <para>�����t�@�C���f�[�^�N���X</para>
	/// </summary>
	[ComVisible(true)]
#if defined(_x64_)
	[Guid("B5E3B9E9-5029-4158-AE70-95A59996644E")]
#else
	[Guid("1B16AF23-BD83-4C49-A1B7-0A3A4F0ECFF5")]
#endif
	[ClassInterface(ClassInterfaceType::None)]
	[ComDefaultInterface(IVoiceFileData::typeid)]
	public ref class VoiceFileData : IVoiceFileData {

	internal:
		/// <summary>
		/// �����t�@�C���̃p�X
		/// </summary>
		System::String^ path;

		/// <summary>
		/// �����t�@�C���̊g���q���������t�@�C����
		/// </summary>
		System::String^ name;

	public:
		/// <summary>
		/// <para>�I�u�W�F�N�g�̕�����</para>
		/// <para>���̉����t�@�C������Ԃ�</para>
		/// </summary>
		/// <returns>���̉����t�@�C����</returns>
		virtual System::String^ ToString() override
		{
			return this->name;
		}

		/// <summary>
		/// �v���p�e�B�F�����t�@�C���̃p�X
		/// </summary>
		property System::String^ Path
		{
			/// <summary>
			/// �����t�@�C���̃p�X���擾����
			/// </summary>
			/// <returns></returns>
			virtual System::String ^get()
			{
				return this->path;
			}
		}

		/// <summary>
		/// �����t�@�C���̖��O�i�g���q�������������j
		/// </summary>
		property System::String^ Name
		{
			/// <summary>
			/// �����t�@�C���̖��O���擾����
			/// </summary>
			/// <returns></returns>
			virtual System::String ^get()
			{
				return this->name;
			}
		}

		/// <summary>
		/// <para>������String^�^�̃R���X�g���N�^</para>
		/// </summary>
		/// <param name="path">�����t�@�C���̃p�X</param>
		/// <param name="name">�����t�@�C����</param>
		VoiceFileData(System::String^path, System::String^name)
		{
			this->path = path;
			this->name = name;
		}

		/// <summary>
		/// <para>������char*�^�̃R���X�g���N�^</para>
		/// </summary>
		/// <param name="path">�����t�@�C���̃p�X</param>
		/// <param name="name">�����t�@�C����</param>
		VoiceFileData(char*path, char*name)
		{
			this->path = gcnew System::String(path);
			this->name = gcnew System::String(name);
		}

		/// <summary>
		/// <para>������HtsVoiceFilelist*�^�̃R���X�g���N�^</para>
		/// </summary>
		/// <param name="data">HtsVoiceFilelist*�^�̉����t�@�C���f�[�^</param>
		/// <returns></returns>
		VoiceFileData(HtsVoiceFilelist*data)
		{
			this->path = gcnew System::String(data->path);
			this->name = gcnew System::String(data->name);
		}

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~VoiceFileData()
		{
			delete this->path;
			delete this->name;
			this->!VoiceFileData();
		}

		/// <summary>
		/// �t�@�C�i���C�U
		/// </summary>
		!VoiceFileData()
		{
		}
	};

	/// <summary>
	/// �����t�@�C���f�[�^�R���N�V�����̃C���^�[�t�F�C�X
	/// </summary>
	[Guid("B73BF2FC-CA54-499E-B7B4-FDFE806E8CFA")]
	[InterfaceType(ComInterfaceType::InterfaceIsDual)]
	public interface class IVoiceCollection : ICollection<VoiceFileData^>
	{
		property int Count { int get(); };
		System::String^ GetPath(int index);
		System::String^ GetName(int index);
		VoiceFileData^ GetItem(int index);
		System::Collections::IEnumerator^ GetEnumerator(void);
	};

	/// <summary>
	/// �����t�@�C���f�[�^�R���N�V����
	/// </summary>
	[ComVisible(true)]
#if defined(_x64_)
	[Guid("ACFB19F9-F94D-45EA-B424-63B415503CB3")]
#else
	[Guid("D5AF2B5D-C932-4A4A-936A-C21CD82D41B2")]
#endif
	[ClassInterface(ClassInterfaceType::None)]
	[ComDefaultInterface(IVoiceCollection::typeid)]
	public ref class VoiceCollection : IVoiceCollection {

	internal:

		/// <summary>
		/// �����t�@�C���f�[�^�̃��X�g
		/// </summary>
		System::Collections::Generic::List<VoiceFileData^>^ m_list = nullptr;

		/// <summary>
		/// <para>�����t�@�C���̃��X�g��NULL�łȂ����`�F�b�N����E</para>
		/// <para>NULL�Ȃ�Η�O�𓊂���B</para>
		/// </summary>
		void check_voicelist()
		{
			if (m_list == nullptr)
			{
				throw gcnew System::Exception("�����G���[�F�����t�@�C�����X�g��NULL�ł��B");
			}
		}

		/// <summary>
		/// <para>�����t�@�C�����X�g�̃C���f�b�N�X�͈̔͂��`�F�b�N����B</para>
		/// <para>�͈͂��Ȃ�΁A��O�𓊂���B</para>
		/// </summary>
		/// <param name="index"></param>
		void check_index(int index)
		{
			if (m_list == nullptr)
			{
				throw gcnew System::Exception("�����G���[�F�����t�@�C�����X�g��NULL�ł��B");
			}

			if (index < 0 || index >= m_list->Count)
			{
				throw gcnew System::Exception("�C���f�b�N�X���͈͊O�ł��B");
			}
		}

	public:

		/// <summary>
		/// ���X�g����v�f���폜����B
		/// </summary>
		/// <param name="item">�폜����v�f</param>
		/// <returns>�폜�������������ǂ���</returns>
		virtual bool Remove(VoiceFileData^ item)
		{
			return m_list->Remove(item);
		}

		/// <summary>
		/// ���X�g���R�s�[����
		/// </summary>
		/// <param name="arr">�R�s�[��</param>
		/// <param name="arrIndex">�R�s�[���J�n����C���f�b�N�X</param>
		virtual void CopyTo(array<VoiceFileData^>^ arr, int arrIndex)
		{
			m_list->CopyTo(arr, arrIndex);
		}

		/// <summary>
		/// �w��v�f���܂ނ��ǂ����𒲂ׂ�B
		/// </summary>
		/// <param name="item">���ׂ�v�f</param>
		/// <returns>�܂�ł��邩�ǂ���</returns>
		virtual bool Contains(VoiceFileData^ item)
		{
			return m_list->Contains(item);
		}

		/// <summary>
		/// �����t�@�C���f�[�^��ǉ�����B
		/// </summary>
		/// <param name="item"></param>
		virtual void Add(VoiceFileData^ item)
		{
			return m_list->Add(item);
		}

		/// <summary>
		/// HtsVoiceFilelist�^�̗v�f���特���t�@�C���f�[�^�����A�ǉ�����B
		/// </summary>
		/// <param name="data"></param>
		virtual void Add(HtsVoiceFilelist* data)
		{
			VoiceFileData^ item = gcnew VoiceFileData(data);
			return m_list->Add(item);
		}

		/// <summary>
		/// ���̃R���N�V�����̂����[�h�I�����[����
		/// </summary>
		property bool IsReadOnly
		{
			/// <summary>
			/// <para>���[�h�I�����[�������擾����B</para>
			/// <para>�U�ɌŒ�</para>
			/// </summary>
			/// <returns>�U</returns>
			virtual bool get()
			{
				return false;
			}
		}

		/// <summary>
		/// GetEnumerator�̎���
		/// </summary>
		/// <returns></returns>
		virtual System::Collections::IEnumerator^ GetEnumerator()
			= System::Collections::IEnumerable::GetEnumerator
		{
			return m_list->GetEnumerator();
		}

		/// <summary>
		/// Generic�^�w���GetEnumerator�̎���
		/// </summary>
		/// <returns></returns>
		virtual System::Collections::Generic::IEnumerator<VoiceFileData^>^ GetEnumerator_generic()
			= System::Collections::Generic::IEnumerable<VoiceFileData^>::GetEnumerator
		{
			return m_list->GetEnumerator();
		}

		/// <summary>
		/// <para>�f�t�H���g�C���f�N�T</para>
		/// <para>�C���f�b�N�X���g���Ĕz��̂悤�ɗv�f�ɃA�N�Z�X����</para>
		/// </summary>
		property VoiceFileData^ default[int]
		{
			/// <summary>
			/// �v�f���擾����
			/// </summary>
			/// <param name="index">�C���f�b�N�X</param>
			/// <returns>�����t�@�C���f�[�^�ւ̃|�C���^</returns>
			VoiceFileData^ get(int index)
			{
			return m_list[index];
			}
		}

		/// <summary>
		/// �������z��L��̃R���X�g���N�^
		/// </summary>
		/// <param name="data">���������X�g</param>
		VoiceCollection(array<VoiceFileData^>^data)
		{
			m_list = gcnew System::Collections::Generic::List<VoiceFileData^>();
			m_list->AddRange(data);
		}

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		VoiceCollection()
		{
			m_list = gcnew System::Collections::Generic::List<VoiceFileData^>();
		}

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~VoiceCollection()
		{
			m_list->Clear();
		}

		/// <summary>
		/// �t�@�C�i���C�U
		/// </summary>
		!VoiceCollection()
		{
		}

		/// <summary>
		/// �w�肳�ꂽ�C���f�b�N�X�̉����t�@�C���f�[�^���擾����
		/// </summary>
		/// <param name="index">�z��Y����</param>
		/// <returns>�����t�@�C���f�[�^</returns>
		virtual VoiceFileData^ GetItem(int index)
		{
			check_voicelist();
			check_index(index);
			return m_list[index];
		}

		/// <summary>
		/// �w�肳�ꂽ�C���f�b�N�X�̉����t�@�C���̃p�X���擾����
		/// </summary>
		/// <param name="index">�z��Y����</param>
		/// <returns>�p�X������</returns>
		virtual System::String^ GetPath(int index)
		{
			check_voicelist();
			check_index(index);
			return m_list[index]->path;
		}

		/// <summary>
		/// �w�肳�ꂽ�C���f�b�N�X�̉����t�@�C���̖��O���擾����
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		virtual System::String^ GetName(int index)
		{
			check_voicelist();
			check_index(index);
			return m_list[index]->name;
		}

		/// <summary>
		/// �����t�@�C���R���N�V�������N���A����
		/// </summary>
		virtual void Clear(void)
		{
			check_voicelist();
			m_list->Clear();
		}

		/// <summary>
		/// �����t�@�C���R���N�V�����̐�
		/// </summary>
		property int Count
		{
			/// <summary>
			/// �J�X�𐔂���
			/// </summary>
			/// <returns></returns>
			virtual int get()
			{
				check_voicelist();
				return m_list->Count;
			}
		}
	};

	/// <summary>
	/// <para>TTS�̂��߂̃C���^�[�t�F�C�X</para>
	/// </summary>
	[Guid("6EEAAEE7-DD5F-44DD-A32F-A30A148E6D7A")]
	[InterfaceType(ComInterfaceType::InterfaceIsDual)]
	public interface class IJTalkTTS
	{
		void Refresh();
		property unsigned int SamplingFrequency {  void set(unsigned int value); }
		property unsigned int S { void set(unsigned int value); }
		property unsigned int Fperiod {  void set(unsigned int value); }
		property unsigned int P {  void set(unsigned int value); }
		property double Alpha {  void set(double value); }
		property double A {  void set(double value); }
		property double Beta {  void set(double value); }
		property double B {  void set(double value); }
		property double Speed {  void set(double value); }
		property double R {  void set(double value); }
		property double AdditionalHalfTone {  void set(double value); }
		property double FM {  void set(double value); }
		property double MSDThreshold {  void set(double value); }
		property double U {  void set(double value); }
		property double GVWeightForSpectrum {  void set(double value); }
		property double JM {  void set(double value); }
		property double GVWeightForLogF0 {  void set(double value); }
		property double JF {  void set(double value); }
		property double Volume {  void set(double value); }
		property double G {  void set(double value); }
		property System::String^ Dic { void set(System::String^ value); }
		property System::String^ VoiceDir {  void set(System::String^ value); }
		property System::String^ Voice { void set(System::String^ value); }
		void SpeakSync(System::String^ text);
		void SpeakAsync(System::String^ text);
		void Stop();
		property bool IsSpeaking {bool get(); }
		void WaitUntilDone();
		void Wait();
		void Wait(int duration);
		void SpeakToFile(System::String^ text, System::String^ file);
		property VoiceCollection ^Voices {VoiceCollection ^get(); }
	};

	/// <summary>
	/// TTS�N���X
	/// </summary>
	[ProgId("OpenJTalk.TTS")]
	[ComVisible(true)]
#if defined(_x64_)
	[Guid("69535960-A7A5-4E9B-8A14-C1CD4BD97734")]
#else
	[Guid("C23F68E0-7D76-4D63-8BA3-8942EE49C6DA")]
#endif
	[ClassInterface(ClassInterfaceType::None)]
	[ComDefaultInterface(IJTalkTTS::typeid)]
	/// <summary>
	/// OpenJTalk ��p���� TextToSpeech ����������N���X
	/// </summary>
	public ref class JTalkTTS : IJTalkTTS {

	internal:
		/// <summary>
		/// ���ʊ֐��ŗp����f�[�^�\����
		/// </summary>
		OpenJTalk *m_openjtalk = NULL;

		/// <summary>
		/// <para>�����t�@�C���f�[�^�̃R���N�V����</para>
		/// <para>VBScript�� For Each �̃O���[�v�Ɏw��\</para>
		/// <para>JScript�� Enumerator() �̈����Ɏw��\</para>
		/// </summary>
		VoiceCollection^ m_voiceCollection = nullptr;

		/// <summary>
		/// <para>openjtalk �\���̂ւ̃|�C���^��NULL���ǂ������ׂ�B</para>
		/// <para>NULL�Ȃ�Η�O�𓊂���B</para>
		/// </summary>
		void check_struct()
		{
			if (!m_openjtalk)
			{
				throw gcnew System::Exception("�����G���[�F�\���̂ւ̃|�C���^��NULL�ł��B");
			}
		}

		/// <summary>
		/// <para>�����t�@�C���f�[�^�̃��X�g�𐶐�����B</para>
		/// <para>�g�p���delete_voice_list���g���ĉ������B</para>
		/// </summary>
		void generate_voice_list()
		{
			check_struct();

			if (m_voiceCollection)
			{
				m_voiceCollection->Clear();
			}
			else
			{
				m_voiceCollection = gcnew VoiceCollection();
			}

			HtsVoiceFilelist *result = OpenJTalk_getHTSVoiceList(m_openjtalk);
			if (result)
			{
				for (HtsVoiceFilelist* list = result; list != NULL; list = list->succ)
				{
					m_voiceCollection->Add(list);
				}
				OpenJTalk_clearHTSVoiceList(m_openjtalk, result);
			}
		}

		/// <summary>
		/// <para>�����t�@�C���f�[�^�̃��X�g���������B</para>
		/// </summary>
		void delete_voice_list()
		{
			check_struct();
			m_voiceCollection->Clear();
		}

	public:

		/// <summary>
		/// <para>�R���X�g���N�^</para>
		/// </summary>
		JTalkTTS()
		{
			m_openjtalk = OpenJTalk_initialize();
			check_struct();
			generate_voice_list();
		}

		/// <summary>
		/// <para>JTalkTTS�N���X�̃f�X�g���N�^</para>
		/// </summary>
		~JTalkTTS()
		{
			delete_voice_list();
			delete m_voiceCollection;
			this->!JTalkTTS();
		}

		/// <summary>
		/// <para>JTalkTTS�N���X�̃t�@�C�i���C�U</para>
		/// </summary>
		!JTalkTTS()
		{
			check_struct();

			OpenJTalk_clear(m_openjtalk);
		}

		/// <summary>
		/// <para>�N���X�̃��t���b�V�����s���B </para>
		/// <para>�E�ݒ�̃N���A</para>
		/// <para>�E�ݒ�t�@�C��������΍ēǂݍ���</para>
		/// </summary>
		virtual void Refresh()
		{
			check_struct();

			OpenJTalk_refresh(m_openjtalk);

		}

		/// <summary>
		/// ���p�\�ȉ����t�@�C���̃R���N�V����
		/// </summary>
		property VoiceCollection^ Voices
		{
			/// <summary>
			/// ���p�\�ȉ����t�@�C���R���N�V�������擾����
			/// </summary>
			/// <returns>���p�\�ȉ����t�@�C���R���N�V����</returns>
			virtual VoiceCollection^get()
			{
				return m_voiceCollection;
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�T���v�����O���g��</para>
		/// </summary>
		property unsigned int SamplingFrequency
		{
			/// <summary>
			/// <para>�T���v�����O���g���̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i1��i�j</param>
			virtual void set(unsigned int value)
			{
				check_struct();

				if (value < 1)
				{
					throw gcnew System::Exception("sampling frequency �̒l��1�ȏ�̐����ł��B");
				}
				OpenJTalk_setSamplingFrequency(m_openjtalk, value);
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�T���v�����O���g��</para>
		/// </summary>
		property unsigned int S
		{
			/// <summary>
			/// <para>�T���v�����O���g���̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i1��i�j</param>
			virtual void set(unsigned int value)
			{
				SamplingFrequency = value;
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�t���[���s���I�h</para>
		/// </summary>
		property unsigned int Fperiod
		{
			/// <summary>
			/// <para>�t���[���s���I�h�̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i1��i�j</param>
			virtual void set(unsigned int value)
			{
				check_struct();

				if (value < 1)
				{
					throw gcnew System::Exception("frame period �̒l��1�ȏ�̐����ł��B");
				}
				OpenJTalk_setFperiod(m_openjtalk, value);
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�t���[���s���I�h</para>
		/// </summary>
		property unsigned int P
		{
			/// <summary>
			/// <para>�t���[���s���I�h�̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i1��i�j</param>
			virtual void set(unsigned int value)
			{
				Fperiod = value;
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�I�[���p�X�l</para>
		/// </summary>
		property double Alpha
		{
			/// <summary>
			/// <para>�I�[���p�X�l�̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i0��d��1�j</param>
			virtual void set(double value)
			{
				check_struct();

				if (value < 0.0 || value > 1.0)
				{
					throw gcnew System::Exception("all-pass constant �̒l��0��1�̊Ԃ̕��������_���ł��B");
				}
				OpenJTalk_setAlpha(m_openjtalk, value);
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�I�[���p�X�l</para>
		/// </summary>
		property double A
		{
			/// <summary>
			/// <para>�I�[���p�X�l�̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i0��d��1�j</param>
			virtual void set(double value)
			{
				Alpha = value;
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�|�X�g�t�B���^�[�W��</para>
		/// </summary>
		property double Beta
		{
			/// <summary>
			/// <para>�|�X�g�t�B���^�[�W���̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i0��d��1�j</param>
			virtual void set(double value)
			{
				check_struct();

				if (value < 0.0 || value > 1.0)
				{
					throw gcnew System::Exception("postfiltering coefficient �̒l��0��1�̊Ԃ̕��������_���ł��B");
				}
				OpenJTalk_setBeta(m_openjtalk, value);
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�|�X�g�t�B���^�[�W��</para>
		/// </summary>
		property double B
		{
			/// <summary>
			/// <para>�|�X�g�t�B���^�[�W���̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i0��d��1�j</param>
			virtual void set(double value)
			{
				Beta = value;
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�X�s�[�`���x</para>
		/// </summary>
		property double Speed
		{
			/// <summary>
			/// <para>�X�s�[�`���x�̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i0��d�j</param>
			virtual void set(double value)
			{
				check_struct();

				if (value < 0.0)
				{
					throw gcnew System::Exception("speech speed rate �̒l��0�ȏ�̕��������_���ł��B");
				}
				OpenJTalk_setSpeed(m_openjtalk, value);
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�X�s�[�`���x</para>
		/// </summary>
		property double R
		{
			/// <summary>
			/// <para>�X�s�[�`���x�̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i0��d�j</param>
			virtual void set(double value)
			{
				Speed = value;
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�ǉ��n�[�t�g�[��</para>
		/// </summary>
		property double AdditionalHalfTone
		{
			/// <summary>
			/// <para>�ǉ��n�[�t�g�[���̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�id�j</param>
			virtual void set(double value)
			{
				check_struct();

				OpenJTalk_addHalfTone(m_openjtalk, value);
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�ǉ��n�[�t�g�[��</para>
		/// </summary>
		property double FM
		{
			/// <summary>
			/// <para>�ǉ��n�[�t�g�[���̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�id�j</param>
			virtual void set(double value)
			{
				AdditionalHalfTone = value;
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�L�� / �������E�l</para>
		/// </summary>
		property double MSDThreshold
		{
			/// <summary>
			/// <para>�L�� / �������E�l���̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i0��d��1�j</param>
			virtual void set(double value)
			{
				check_struct();

				if (value < 0.0 || value > 1.0)
				{
					throw gcnew System::Exception("voiced/unvoiced threshold �̒l��0��1�̊Ԃ̕��������_���ł��B");
				}
				OpenJTalk_setMsdThreshold(m_openjtalk, value);
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�L�� / �������E�l</para>
		/// </summary>
		property double U
		{
			/// <summary>
			/// <para>�L�� / �������E�l���̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i0��d��1�j</param>
			virtual void set(double value)
			{
				MSDThreshold = value;
			}
		}

		/// <summary>
		/// <para>�n����ϓ��̏d�݂�ݒ肷��</para>
		/// </summary>
		/// <param name="i">�X�g���[���C���f�b�N�X�ii=0,1�j</param>
		/// <param name="f">GV�d�݁i0��d�j</param>
		virtual void  SetGVWeight(size_t i, double f)
		{
			check_struct();

			if (i != 0 && i != 1)
			{
				throw gcnew System::Exception("stream index �̒l��0��1�̐����ł��B");
			}
			if (f < 0.0)
			{
				throw gcnew System::Exception("GV weight �̒l��0�ȏ�̕��������_���ł��B");
			}
			OpenJTalk_setGvWeight(m_openjtalk, i, f);
		}

		/// <summary>
		/// <para>�v���p�e�B�F�X�y�N�g�����n����ϓ��̏d��</para>
		/// </summary>
		property double GVWeightForSpectrum
		{
			/// <summary>
			/// <para>�X�y�N�g�����n����ϓ��̏d�݂̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i0��d�j</param>
			virtual void set(double value)
			{
				check_struct();

				if (value < 0.0)
				{
					throw gcnew System::Exception("weight of GV for spectrum �̒l��0�ȏ�̕��������_���ł��B");
				}
				OpenJTalk_setGvWeightForSpectrum(m_openjtalk, value);
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�X�y�N�g�����n����ϓ��̏d��</para>
		/// </summary>
		property double JM
		{
			/// <summary>
			/// <para>�X�y�N�g�����n����ϓ��̏d�݂̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i0��d�j</param>
			virtual void set(double value)
			{
				GVWeightForSpectrum = value;
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�FF0�n����ϓ��d��</para>
		/// </summary>
		property double GVWeightForLogF0
		{
			/// <summary>
			/// <para>F0�n����ϓ��d�݂̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i0��d�j</param>
			virtual void set(double value)
			{
				check_struct();

				if (value < 0.0)
				{
					throw gcnew System::Exception("weight of GV for log F0 �̒l��0�ȏ�̕��������_���ł��B");
				}
				OpenJTalk_setGvWeightForLogF0(m_openjtalk, value);
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�FF0�n����ϓ��d��</para>
		/// </summary>
		property double JF
		{
			/// <summary>
			/// <para>F0�n����ϓ��d�݂̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�i0��d�j</param>
			virtual void set(double value)
			{
				GVWeightForLogF0 = value;
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�{�����[��</para>
		/// </summary>
		property double Volume
		{
			/// <summary>
			/// <para>�{�����[���̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�id�j</param>
			virtual void set(double value)
			{
				check_struct();

				OpenJTalk_setVolume(m_openjtalk, value);
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�{�����[��</para>
		/// </summary>
		property double G
		{
			/// <summary>
			/// <para>�{�����[���̐ݒ�</para>
			/// </summary>
			/// <param name="value">�l�id�j</param>
			virtual void set(double value)
			{
				Volume = value;
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�F�����t�H���_</para>
		/// </summary>
		property System::String^ Dic
		{
			/// <summary>
			/// <para>�����t�H���_�̐ݒ�</para>
			/// </summary>
			/// <param name="path">�p�X������</param>
			virtual void set(System::String^path)
			{
				check_struct();

				if (!path)
				{
					throw gcnew System::Exception("�����t�H���_������������ւ̃|�C���^��NULL�ł��B");
				}
				if (!Directory::Exists(path))
				{
					throw gcnew System::Exception("�����t�H���_��������܂���B");
				}
				marshal_context ctx;
				const wchar_t*str = ctx.marshal_as<const wchar_t*>(path);
				if (!OpenJTalk_setDic_u16(m_openjtalk, (const char16_t*)str))
				{
					throw gcnew System::Exception("�����t�H���_��ݒ�ł��܂���BUTF-8�����̎����ł͂Ȃ���������܂���B");
				}
			}
		}

		/// <summary>
		/// �v���p�e�B�F�����t�@�C���t�H���_
		/// </summary>
		property System::String^ VoiceDir
		{
			/// <summary>
			/// <para>�����t�@�C���t�H���_�̐ݒ�</para>
			/// </summary>
			/// <param name="path">�p�X������</param>
			virtual void set(System::String^path)
			{
				check_struct();

				if (!path)
				{
					throw gcnew System::Exception("�����t�@�C���t�H���_������������ւ̃|�C���^��NULL�ł��B");
				}
				if (!Directory::Exists(path))
				{
					throw gcnew System::Exception("�����t�@�C���t�H���_��������܂���B");
				}
				delete_voice_list();
				marshal_context ctx;
				const wchar_t* str = ctx.marshal_as<const wchar_t*>(path);
				if (!OpenJTalk_setVoiceDir_u16(m_openjtalk, (const char16_t*)str))
				{
					throw gcnew System::Exception("�����t�@�C���t�H���_��ݒ�ł��܂���B");
				}
				generate_voice_list();
			}
		}

		/// <summary>
		/// <para>�v���p�e�B�i�ݒ�̂݁j</para>
		/// <para>�ȍ~�̔����Ŏg�p���鉹���t�@�C���̐ݒ�</para>
		/// <para>�O�ʂ�̎w����@</para>
		/// <para>�E��΃p�X...�t�@�C���̒��ڎw��</para>
		/// <para>�E���΃p�X�i�g���q�L��j...�����t�@�C���t�H���_���ł̑��Ύw��</para>
		/// <para>�E���O�̂݁i�g���q�����j...�����t�@�C���t�H���_����T��</para>
		/// <para>�T���ɂ��āF</para>
		/// <para>�T���͈͂ɕ����K��������̂������Ă��A�ŏ��Ɍ��������̂Ƃ���B</para>
		/// <para>���̂Ƃ��̒T��������readdir�̏����Ɉˑ����Ă���B</para>
		/// <para>�T�����ɂ̓��C���h�J�[�h�i*?�j���g�p�ł���B</para>
		/// <para>�T���Ώۂ������Ƃ���1000�t�@�C���T�����Ă�������Ȃ���ΒT���𒆎~����B</para>
		/// </summary>
		property System::String^ Voice
		{
			/// <summary>
			/// <para>�ȍ~�̔����Ŏg�p���鉹���t�@�C���̐ݒ�</para>
			/// </summary>
			/// <param name="path">�����t�@�C��������������</param>
			virtual void set(System::String^path)
			{
				check_struct();

				if (!path)
				{
					throw gcnew System::Exception("�����t�@�C��������������ւ̃|�C���^��NULL�ł��B");
				}
				if (path->Length == 0)
				{
					throw gcnew System::Exception("�����t�@�C�������������񂪋�ł��B");
				}
				marshal_context ctx;
				const wchar_t* str = ctx.marshal_as<const wchar_t*>(path);
				if (!OpenJTalk_setVoice_u16(m_openjtalk, (const char16_t*)str))
				{
					throw gcnew System::Exception("�����t�@�C����ݒ�ł��܂���B");
				}
			}
		}

		/// <summary>
		/// <para>������������B</para>
		/// <para>�ǂݏグ���I���܂ŏ����͖߂�Ȃ��B</para>
		/// <para>�������Ȃ�΁A������I�������Ĕ�������B</para>
		/// </summary>
		/// <param name="text">�ǂݏグ������</param>
		virtual void SpeakSync(System::String^ text)
		{
			check_struct();

			if (!text)
			{
				throw gcnew System::Exception("�ǂݏグ������ւ̃|�C���^��NULL�ł��B");
			}
			marshal_context ctx;
			const wchar_t* str = ctx.marshal_as<const wchar_t*>(text);
			OpenJTalk_speakSync_u16(m_openjtalk, (const char16_t*)str);
		}

		/// <summary>
		/// <para>�񓯊���������B</para>
		/// <para>�ǂݏグ�J�n��A�������߂��Ă���B</para>
		/// <para>�������Ȃ�΁A������I�������Ĕ�������B</para>
		/// </summary>
		/// <param name="text">�ǂݏグ������</param>
		virtual void SpeakAsync(System::String^ text)
		{
			check_struct();

			if (!text)
			{
				throw gcnew System::Exception("�ǂݏグ������ւ̃|�C���^��NULL�ł��B");
			}
			marshal_context ctx;
			const wchar_t* str = ctx.marshal_as<const wchar_t*>(text);
			OpenJTalk_speakAsync_u16(m_openjtalk, (const char16_t*)str);
		}

		/// <summary>
		/// �������Ȃ�΁A������������~����B
		/// </summary>
		virtual void  Stop()
		{
			check_struct();

			OpenJTalk_stop(m_openjtalk);
		}

		/// <summary>
		/// <para>�v���p�e�B�F�񓯊����������ǂ���</para>
		/// </summary>
		property bool IsSpeaking
		{
			/// <summary>
			/// ���������ǂ������ׂ�
			/// </summary>
			/// <returns>���������ǂ����̐^�U�l</returns>
			virtual bool get()
			{
				check_struct();

				return OpenJTalk_isSpeaking(m_openjtalk);
			}
		}

		/// <summary>
		/// <para>�񓯊��������Ȃ�΁A��~����܂őҋ@����B</para>
		/// <para>Wait(void)�̕ʖ�</para>
		/// </summary>
		virtual void WaitUntilDone()
		{
			check_struct();

			OpenJTalk_waitUntilDone(m_openjtalk);
		}

		/// <summary>
		/// <para>�w��~���b�̊ԑҋ@����B</para>
		/// <para>�񓯊������͑����B</para>
		/// <para>duration��0�̂Ƃ��́AWaitUntilDone�Ɠ�������</para>
		/// </summary>
		/// <param name="duration">�ҋ@���ԁi�~���b�j</param>
		virtual void Wait(int duration)
		{
			check_struct();

			if (duration == 0)
			{
				OpenJTalk_waitUntilDone(m_openjtalk);
			}
			else
			{
				OpenJTalk_wait(m_openjtalk, duration);
			}
		}

		/// <summary>
		/// <para>�������Ă���ԑҋ@����B</para>
		/// <para>�񓯊������͑����B</para>
		/// <para>WaitUntilDone�̕ʖ�</para>
		/// </summary>
		virtual void Wait()
		{
			check_struct();

			OpenJTalk_waitUntilDone(m_openjtalk);
		}

		/// <summary>
		/// <para>�w��t�@�C���ɕ�����̉�����ۑ�����</para>
		/// </summary>
		/// <param name="text">������</param>
		/// <param name="file">�t�@�C����</param>
		virtual void SpeakToFile(System::String^text, System::String^file)
		{
			check_struct();

			if (!text)
			{
				throw gcnew System::Exception("�ǂݏグ������ւ̃|�C���^��NULL�ł��B");
			}
			if (text->Length == 0)
			{
				throw gcnew System::Exception("�ǂݏグ�����񂪋�ł��B");
			}
			if (file->Length == 0)
			{
				throw gcnew System::Exception("�t�@�C���������񂪋�ł��B");
			}
			marshal_context ctx;
			const wchar_t* str_text = ctx.marshal_as<const wchar_t*>(text);
			const wchar_t* str_file = ctx.marshal_as<const wchar_t*>(file);
			if (!OpenJTalk_speakToFile_u16(m_openjtalk, (const char16_t*)str_text, (const char16_t*)str_file))
			{
				throw gcnew System::Exception("�����t�@�C���̍쐬���ɃG���[���������܂����B");
			}
		}
	};
}

