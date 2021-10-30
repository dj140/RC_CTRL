#include "BSP.h"
#include "extEEPROM/extEEPROM.h"

/*�ⲿEEPROM*/
extEEPROM eeprom(kbits_256, 1, 64, 0x50);

/*��ʼ�����ַ*/
#define START_ADDR      64

/*���ע���������*/
#define RegDataList_MAX 32

/*��ȡ��ʱ����*/
#define DataReadTimeOut  5000 /*[ms]*/

/*������־����ӿ�*/
#define DS_DEBUG(data)            //Serial.println(data);
#define DS_DEBUG_FMT(format, ...) //Serial.printf(format, ##__VA_ARGS__)

/*���ֽڶ���*/
#pragma pack(1)
/*
---------------------------------------------���ݽṹ--------------------------------------------
|                     ֡ͷ                       |                 �û�����
| �û������ܳ� | �û������ܸ��� | �û�����У��� | ����1��С |  ����1  | ����2��С |  ����2  |...
|     2Byte    |     2Byte      |     4Byte      |   2Byte   |  xByte  |   2Byte   |  xByte  |...
*/

/*֡ͷ���ݽṹ*/
typedef struct {
    uint16_t DataLength;/*�û������ܳ�*/
    uint16_t DataCntSum;/*�û������ܸ���*/
    uint32_t CheckSum;/*�û�����У���*/
} EEPROM_DataHead_t;

/*�������ݽṹ*/
typedef struct {
    uint8_t* pData;/*�û����ݵ�ַ*/
    uint16_t Size;/*�û����ݴ�С*/
} EEPROM_RegList_t;
#pragma pack()

/*�û������б�*/
static EEPROM_RegList_t DataReg_List[RegDataList_MAX] = {0};

/*�û�����ע���¼��ĸ���*/
static uint16_t DataReg_Cnt = 0;

/*��ǰ��д�ĵ�ַƫ����*/
static uint16_t DataReg_OffsetAddr = 0;

/**
  * @brief  EEPROM��ȡ�ӿ�
  * @param  addr:Ҫ��ȡ�ĵ�ַ
  * @retval �����ַ���������
  */
static uint8_t EEPROM_Read(uint32_t addr)
{
    DS_DEBUG_FMT(">> R: addr=%d data=0x%x\r\n", addr, eeprom.read(START_ADDR + addr));
    return eeprom.read(START_ADDR + addr);
}

/**
  * @brief  ��EEPROM��ȡһ������
  * @param  addr:Ҫ��ȡ����ʼ��ַ
  * @param  pdata:�������ݵ���ʼ��ַ
  * @param  size:�������ݵĸ���
  * @retval ��
  */
static void EEPROM_Read(uint32_t addr, void* pdata, uint32_t size)
{
    for(uint32_t i = 0; i < size; i++)
    {
        ((uint8_t*)pdata)[i] = EEPROM_Read(addr + i);
    }
}

/**
  * @brief  EEPROMд���ݽӿ�
  * @param  addr:Ҫ��ȡ�ĵ�ַ
  * @param  data:Ҫд�������
  * @retval ��
  */
static void EEPROM_Write(uint32_t addr, uint8_t data)
{
    DS_DEBUG_FMT("<< W: addr=%d data=0x%x\r\n", addr, data);
    eeprom.update(START_ADDR + addr, data);
}

/**
  * @brief  ��EEPROMд��һ������
  * @param  addr:Ҫд�����ʼ��ַ
  * @param  pdata:��д���ݵ���ʼ��ַ
  * @param  size:д�����ݵĸ���
  * @retval ��
  */
static void EEPROM_Write(uint32_t addr, void* pdata, uint32_t size)
{
    for(uint32_t i = 0; i < size; i++)
    {
        EEPROM_Write(addr + i, ((uint8_t*)pdata)[i]);
    }
}

/**
  * @brief  ��ȡ��һ����ַ������
  * @param  ��
  * @retval ��һ����ַ���������
  */
static uint8_t EEPROM_ReadNext()
{
    uint8_t data = EEPROM_Read(DataReg_OffsetAddr);
    DataReg_OffsetAddr++;
    return data;
}

/**
  * @brief  ����һ����ַд����
  * @param  data:��д������
  * @retval ��
  */
static void EEPROM_WriteNext(uint8_t data)
{
    EEPROM_Write(DataReg_OffsetAddr, data);
    DataReg_OffsetAddr++;
}

/**
  * @brief  EEPROM��ʼ��
  * @param  ��
  * @retval �������
  */
uint8_t EEPROM_Init()
{
    DEBUG_FUNC_LOG();
    return eeprom.begin(eeprom.twiClock100kHz);
	// test eeprom 
//	uint8_t retval = eeprom.begin(eeprom.twiClock100kHz);
//	
//		for(int i = 0; i < 1024; i++)
//		{
//				eeprom.write(i,i);
//		}
//		for(int i = 0; i < 1024; i++)
//		{
//				uint8_t data = eeprom.read(i);
//				Serial.println(data);
////				if(i != data)
////				{
////					
////						while(1);
////				}
//		}
//		while(1);
//		return retval;
}

/**
  * @brief  ע���������ͱ���
  * @param  *pdata:ָ����������ݵ�ָ��
  * @param  size:���ݴ�С
  * @retval true�ɹ� falseʧ��
  */
bool EEPROM_Register(void *pdata, uint16_t size)
{
    if(DataReg_Cnt == RegDataList_MAX)
        return false;
    
    DataReg_List[DataReg_Cnt].pData = (uint8_t*)pdata;
    DataReg_List[DataReg_Cnt].Size = size;
    DataReg_Cnt++;
    return true;
}

/**
  * @brief  ����ע�����������
  * @param  ��
  * @retval true�ɹ� falseʧ��
  */
bool EEPROM_SaveAll()
{
    DS_DEBUG(__FUNCTION__);
    
    /*��ʼ��֡ͷ*/
    EEPROM_DataHead_t head;
    memset(&head, 0, sizeof(head));
    
    /*���жϣ���ֹ���ݴ۸�*/
    noInterrupts();
    
    /*����֡ͷ��Ϣ*/
    /*�û�ע�����ݵ��ܸ���*/
    head.DataCntSum = DataReg_Cnt;

    /*����ע���б�,����У����Ϣ*/
    for(uint32_t cnt = 0; cnt < DataReg_Cnt; cnt++)
    {
        /*�û������ܳ�*/
        uint16_t length = (sizeof(DataReg_List[cnt].Size) + DataReg_List[cnt].Size);
        
        /*�û�����У���ܺ�*/
        uint32_t checksum = 0;
        uint16_t size = DataReg_List[cnt].Size;
        checksum += highByte(size);
        checksum += lowByte(size);
        for(uint32_t offset = 0; offset < size; offset++)
        {
            checksum += (DataReg_List[cnt].pData)[offset];
        }
        
        DS_DEBUG_FMT("CNT %d : size = %d, length = %d, checksum = %d\r\n", cnt, size, length, checksum);
        
        head.DataLength += length;
        head.CheckSum += checksum;
    }

    /*д��֡ͷ��Ϣ*/
    EEPROM_Write(0, &head, sizeof(head));
    DS_DEBUG("Write head");
    DS_DEBUG_FMT(".DataLength   = %d\r\n", head.DataLength);
    DS_DEBUG_FMT(".DataCntSum   = %d\r\n", head.DataCntSum);
    DS_DEBUG_FMT(".DataCheckSum = %d\r\n", head.CheckSum);
    
    /*�Ƶ�֡ͷ֮��,�����û�������*/
    DataReg_OffsetAddr = sizeof(head);

    /*����ע���б�д���û�����*/
    for(uint32_t i = 0; i < DataReg_Cnt; i++)
    {
        uint16_t size = DataReg_List[i].Size;
        EEPROM_WriteNext(highByte(size));
        EEPROM_WriteNext(lowByte(size));
        for(uint32_t offset = 0; offset < size; offset++)
        {
            EEPROM_WriteNext((DataReg_List[i].pData)[offset]);
        }
    }
    
    /*�ж��Ƿ�д��ɹ�*/
    bool retval =  EEPROM_ReadAll();
    
    /*���������ж�*/
    interrupts();
    
    return retval;
}

/**
  * @brief  ��ȡע�����������
  * @param  ��
  * @retval true�ɹ� falseʧ��
  */
bool EEPROM_ReadAll()
{
    DS_DEBUG(__FUNCTION__);
    
    /*��ʼ��֡ͷ*/
    EEPROM_DataHead_t head;
    memset(&head, 0, sizeof(head));
    
    /*��ȡ֡ͷ��Ϣ*/
    EEPROM_Read(0, &head, sizeof(head));
    DS_DEBUG("Read head");
    DS_DEBUG_FMT(".DataLength   = %d\r\n", head.DataLength);
    DS_DEBUG_FMT(".DataCntSum.  = %d\r\n", head.DataCntSum);
    DS_DEBUG_FMT(".DataCheckSum = %d\r\n", head.CheckSum);

    /*��ʼ���û�����У���*/
    uint32_t UserDataCheckSum = 0;
    uint32_t StartReadTime = millis();
    
    /*�Ƶ��û�������*/
    DataReg_OffsetAddr = sizeof(head);

    /*����У���*/
    for(uint16_t i = 0; i < head.DataLength; i++)
    {
        /*��ȡ�Ƿ�ʱ*/
        if(millis() - StartReadTime > DataReadTimeOut)
        {
            DS_DEBUG("ERROR! data read timeout");
            return false;
        }
        
        UserDataCheckSum += EEPROM_ReadNext();
    }

    /*У���û������Ƿ���ע���б�ƥ��*/
    /*���У���*/
    if(UserDataCheckSum != head.CheckSum)
    {
        DS_DEBUG_FMT("ERROR! UserDataCheckSum = %d, not PASS\r\n", UserDataCheckSum);
        return false;
    }
    
    /*���ע�����*/
    if(head.DataCntSum != DataReg_Cnt)
    {
        DS_DEBUG_FMT("ERROR! DataCntSum = %d, not PASS\r\n", head.DataCntSum);
        return false;
    }
    
    /*�Ƶ��û�������*/
    DataReg_OffsetAddr = sizeof(head);
    
    /*����ע���б�*/
    for(uint32_t i = 0; i < head.DataCntSum; i++)
    {
        uint8_t high = EEPROM_ReadNext();
        uint8_t low = EEPROM_ReadNext();

        uint16_t UserSize = high << 8 | low;

        /*/У���Ƿ����û�ע���б�ƥ��*/
        if(UserSize != DataReg_List[i].Size)
        {
            DS_DEBUG_FMT("ERROR! UserSize = %d, not PASS\r\n", UserSize);
            return false;
        }

        /*����ȡ������д��ע���б���pDataָ��ָ�������*/
        for(uint32_t offset = 0; offset < UserSize; offset++)
            (DataReg_List[i].pData)[offset] = EEPROM_ReadNext();
    }
    
    /*��ȡ�ɹ�*/
    DS_DEBUG("Read and check success");
    return true;
}
