#pragma once

#include <LibVoice/LibVoice.h>

class CTeacherVoice : public ITeacherVoice
{
public:
	CTeacherVoice(void);
	~CTeacherVoice(void);

public:
	BOOL Create(GUID& guidIn, 
				GUID& guidOut, 
				int nFormat,
				BOOL bEnableProcessor,
				DWORD dwSSRC,
				HWND hWndMeter = NULL,
				DWORD dwMsgMeter = 0);

	virtual void Destroy();

	// Side Tone
	virtual BOOL BeginMonitor(); 
	virtual void StopMonitor();
	virtual BOOL IsMonitoring();

	// Send side
	virtual BOOL BeginSendGlobalVoice(DWORD dwDestIpAddress, WORD wPort, DWORD dwLocalIpAddress, WORD wLocalPort);
	virtual void StopSendGlobalVoice();
	virtual BOOL IsSendingGlobalVoice();
	virtual BOOL ResetSendGlobalVoice(DWORD dwDestIpAddress, WORD wPort, DWORD dwLocalIpAddress, WORD wLocalPort);

	virtual void SetMainInputMute(BOOL bMute);
	virtual BOOL IsMainInputMuted();

	virtual BOOL AddMixerItem(IVoIPSource * pSource);
	virtual void RemoveMixerItem(IVoIPSource * pSource);

	// Receive side
	virtual BOOL BeginRecvGlobalVoice(DWORD dwDestIpAddress, WORD wPort, DWORD dwLocalIpAddress, WORD wLocalPort);
	virtual void StopRecvGlobalVoice();
	virtual BOOL IsRecvingGlobalVoice();
	virtual BOOL ResetRecvGlobalVoice(DWORD dwDestIpAddress, WORD wPort, DWORD dwLocalIpAddress, WORD wLocalPort);

	virtual LONG GetVoiceMeter();

	int GetSamplesPerSec();
	int GetChannels();
	int GetSamplesPerFrame();
	int GetMaxEncodedFrame();

	void SetEnableStreamCallback(IEnableStreamCallback* pCallback) {
		if (m_pVoiceRender) {
			m_pVoiceRender->SetEnableStreamCallback(pCallback);
		}
	}
	void EnableStream(DWORD dwSSRC, BOOL bEnable) {
		if (m_pVoiceRender) {
			m_pVoiceRender->EnableStream(dwSSRC, bEnable);
		}
	}
	void EnableAllStreams(BOOL bEnable) {
		if (m_pVoiceRender) {
			m_pVoiceRender->EnableAllStreams(bEnable);
		}
	}

	int GetVoiceCaptureGain()
	{
		return m_pVolumeControl->GetGain();
	}
	void SetVoiceCaptureGain(int nGain)
	{
		m_pVolumeControl->SetGain(nGain);
	}

private:

	CVoiceCapture*					m_pVoiceCapture;
	IAudioJitterBufferModule*		m_pJBufferRender;
	IDSoundRendererModule*			m_pDSoundRenderer;
	CRTPUDPVoiceSender*				m_pVoiceSenderGlobal;
	IVolumeControlModule*			m_pVolumeControl;
	IPushedPassiveWaveMixerModule*	m_pPushedPassiveWaveMixer;
	CRTPUDPVoiceRender*				m_pVoiceRender;

	CSourceMap m_mapSources;

	VOICE_FORMAT_INFO m_vfi;

	int		m_nFormat;
	GUID	m_guidIn;
	GUID	m_guidOut;
	BOOL	m_bEnableProcessor;
	DWORD	m_dwSSRC;

	BOOL	m_bCreate;
	BOOL	m_bMonitoring;
	BOOL	m_bSendGlobal;
	BOOL	m_bReceive;

	int		m_nGain;

	HWND	m_hWndMeter;
	DWORD	m_dwMsgMeter;
};

BOOL ITeacherVoice::Create(GUID& guidIn, 
			GUID& guidOut, 
			int nFormat,
			BOOL bEnableProcessor,
			DWORD dwSSRC,
			HWND hWndMeter,
			DWORD dwMsgMeter,
			ITeacherVoice*& pInstance)
{
	CTeacherVoice* pTeacherVoice = new CTeacherVoice();
	if (NULL == pTeacherVoice)
		return FALSE;

	if (!pTeacherVoice->Create(guidIn, 
			guidOut, 
			nFormat,
			bEnableProcessor,
			dwSSRC,
			hWndMeter,
			dwMsgMeter))
	{
		pTeacherVoice->Destroy();
		return FALSE;
	}

	pInstance = (ITeacherVoice *)pTeacherVoice;
	return TRUE;
}
