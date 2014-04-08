#include "HSBufferPropInterface.h"


HSBufferPropInterface::HSBufferPropInterface(void)
{
	this->Reset();

	this->schedule(schedule_selector(HSBufferPropInterface::Updata));
}


HSBufferPropInterface::~HSBufferPropInterface(void)
{
}

void HSBufferPropInterface::Reset()
{
	m_pRecBegin = NULL;
	m_pRecEnd = NULL;

	m_pFuncBegin = NULL;
	m_pFuncEnd = NULL;

	m_fDurationTime = 0.f;
	m_fTakeTime = 0.f;

	m_bufferStart = BufferStart_Idle;
}

void HSBufferPropInterface::Updata( float dt )
{

	switch(m_bufferStart)
	{
	case BufferStart_Listening:
		{
			if (!m_pRecBegin || !m_pFuncBegin)
			{
				break;
			}
			bool isTriggBegin = (m_pRecBegin->*m_pFuncBegin)();
			if (isTriggBegin)
			{
				m_bufferStart = BufferStart_LogicBegin;
			}
		}
		break;
	case BufferStart_LogicBegin:
		{
			bool isTriggEnd = this->LogicBegin(dt);
			if (isTriggEnd)
			{
				m_bufferStart = BufferStart_LogicEnd;
			}
		}
		break;
	case BufferStart_LogicEnd:
		{
			
			bool isOver = this->LogicEnd(dt);

			if (m_fTakeTime > m_fDurationTime)
			{
				//达到持续时间也结束
				isOver = true;

				this->LogicCountDown(dt);

			}else{
				m_fTakeTime += dt;
			}
			if (isOver)
			{
				if (m_pRecEnd && m_pFuncEnd)
				{
					(m_pRecEnd->*m_pFuncEnd)();
				}
				
				m_bufferStart = BufferStart_Idle;
			}
		}
		break;
	default:
		{

		}
		break;
	}
}

void HSBufferPropInterface::SetListerBufferBegin( CCObject* pRec,BufferBegin isBegin )
{
	m_pRecBegin = pRec;
	m_pFuncBegin = isBegin;

	m_bufferStart = BufferStart_Listening;
}

void HSBufferPropInterface::SetListerBufferEnd( CCObject* pRec,BufferEnd isEnd )
{
	m_pRecEnd = pRec;
	m_pFuncEnd = isEnd;
}

void HSBufferPropInterface::SetDurationTime( float dt )
{
	this->m_fDurationTime = dt;
}

float HSBufferPropInterface::GetDurationTime()
{
	return this->m_fDurationTime;
}

