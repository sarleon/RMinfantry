

#ifndef __CONFIG_H
#define __CONFIG_H


#define DEBUGECONTROLRC             0           //debugģʽң�ؿ���
#define USEESP8266orOLEDorOLED      0           //1 ʹ��ESP8266���ز���ϵͳ����           0 ʹ��oled��ʾװ̬

/***************************************   �� �����ֲ���  �� **********************************************/
#define INFANTRY                    1           //1��Ħ   2����˹��   3��ʿ��    4 ��ë   5 ����       6 СӢ��       7 ����

#if INFANTRY == 1               //��Ħ������

    #define FRICMOTORWORKINGSPEED           275         //Ħ���ֹ����ٶ�(170)
    #define POKESTRUCKDEALLINES             400         //�������������ת��������
    #define CHASSISMAXPOWERRATE             1.0F        //�������Ƽ��޹��ʣ�80W������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
    #define POKESTEPSPEED                   -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
    #define POKESTEPMINTIMECRACK            265         //������Сʱ������ms��
    #define MAXWORKINGSPEED                 850         //�����˶��ٶȣ����900��
    #define DEPOTABSPITCH                   -8.0F       //������վ��̨pitch���ԽǶ�ֵ��0Ϊˮƽ��-20 ~ 20��  
    #define SNEAKSPEED                      150         //Ǳ���ٶ�
    #define SWINGMODELIMIT                  30          //ҡ��ģʽ�����޷�(�����޸ģ����ø���40�������ģʽ����ʧЧ)
    #define SWINGMODEOMEGA                  90          //ҡ��ģʽ���ٶ�
    #define CIRCLEMODEOMEGA                 300         //ȦȦģʽ���ٶ�
    #define CIRCLEMODEDELAY                 10000       //ȦȦģʽ�ܵ��˺���תʱ��  
    #define QESPINSPEED                     2.5F        //QE�����ٶ�
    #define MOUSESPINSPEED                  50.0F       //��������ٶ�   
    #define AUTOSHOTDISTANCE                3.2F        //�Զ���������޷�
    #define AUTOSHOTANGLE                   30          //�Զ�����Ƕ��޷� 
    #define BIGSAMPLEOFFSETXPARAM           0.005       //���X�����ƫ�Ƶ��ڱ���
    #define BIGSAMPLEOFFSETYPARAM           0.005       //���X�����ƫ�Ƶ��ڱ���
    #define ENCODERTOABSANGLEOFFSETPARAM    1         //�ɱ������ӵ��������Ǽ�����̨���ԽǶ�ʱ������֭ƫ��˲������ڽ���ƫ��
    
#elif INFANTRY == 2               //����˹�Ӳ�����

    #define FRICMOTORWORKINGSPEED           155         //Ħ���ֹ����ٶ�(170)
    #define CHASSISMAXPOWERRATE             0.82F       //�������Ƽ��޹��ʣ�80W������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
    #define POKESTEPSPEED                   -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
    #define POKESTRUCKDEALLINES             400         //�������������ת��������
    #define POKESTEPMINTIMECRACK            265         //������Сʱ������ms��
    #define MAXWORKINGSPEED                 850         //�����˶��ٶȣ����900��
    #define DEPOTABSPITCH                   -8.0F       //������վ��̨pitch���ԽǶ�ֵ��0Ϊˮƽ��-20 ~ 20��  
    #define SNEAKSPEED                      50         //Ǳ���ٶ�
    #define SWINGMODELIMIT                  30          //ҡ��ģʽ�����޷�(�����޸ģ����ø���40�������ģʽ����ʧЧ)
    #define SWINGMODEOMEGA                  90          //ҡ��ģʽ���ٶ�
    #define CIRCLEMODEOMEGA                 300         //ȦȦģʽ���ٶ�
    #define CIRCLEMODEDELAY                 10000       //ȦȦģʽ�ܵ��˺���תʱ�� 
    #define QESPINSPEED                     1.0F        //QE�����ٶ�   
    #define MOUSESPINSPEED                  50.0F       //��������ٶ� 
    #define AUTOSHOTDISTANCE                3.2F        //�Զ���������޷�
    #define AUTOSHOTANGLE                   30          //�Զ�����Ƕ��޷�  
    #define BIGSAMPLEOFFSETXPARAM           0.005       //���X�����ƫ�Ƶ��ڱ���
    #define BIGSAMPLEOFFSETYPARAM           0.005       //���X�����ƫ�Ƶ��ڱ���
    #define ENCODERTOABSANGLEOFFSETPARAM    1         //�ɱ������ӵ��������Ǽ�����̨���ԽǶ�ʱ������֭ƫ��˲������ڽ���ƫ�� 

#elif INFANTRY == 3               //��ʿ�������

    #define FRICMOTORWORKINGSPEED           264         //Ħ���ֹ����ٶ�(170)
    #define POKESTRUCKDEALLINES             400         //�������������ת��������
    #define CHASSISMAXPOWERRATE             0.82F       //�������Ƽ��޹��ʣ�80W������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
    #define POKESTEPSPEED                   -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
    #define POKESTEPMINTIMECRACK            265         //������Сʱ������ms��
    #define MAXWORKINGSPEED                 850         //�����˶��ٶȣ����900��
    #define DEPOTABSPITCH                   -8.0F       //������վ��̨pitch���ԽǶ�ֵ��0Ϊˮƽ��-20 ~ 20��  
    #define SNEAKSPEED                      150         //Ǳ���ٶ�
    #define SWINGMODELIMIT                  30          //ҡ��ģʽ�����޷�(�����޸ģ����ø���40�������ģʽ����ʧЧ)
    #define SWINGMODEOMEGA                  90          //ҡ��ģʽ���ٶ�
    #define CIRCLEMODEOMEGA                 300         //ȦȦģʽ���ٶ�
    #define CIRCLEMODEDELAY                 10000       //ȦȦģʽ�ܵ��˺���תʱ��  
    #define QESPINSPEED                     1.0F        //QE�����ٶ�   
    #define MOUSESPINSPEED                  50.0F       //��������ٶ� 
    #define AUTOSHOTDISTANCE                3.2F        //�Զ���������޷�
    #define AUTOSHOTANGLE                   30          //�Զ�����Ƕ��޷�  
    #define BIGSAMPLEOFFSETXPARAM           0.005       //���X�����ƫ�Ƶ��ڱ���
    #define BIGSAMPLEOFFSETYPARAM           0.005       //���X�����ƫ�Ƶ��ڱ���
    #define ENCODERTOABSANGLEOFFSETPARAM    1         //�ɱ������ӵ��������Ǽ�����̨���ԽǶ�ʱ������֭ƫ��˲������ڽ���ƫ��

#elif INFANTRY == 4               //��ë

    #define FRICMOTORWORKINGSPEED           250         //Ħ���ֹ����ٶ�(230)
    #define POKESTRUCKDEALLINES             400          //�������������ת��������
    #define CHASSISMAXPOWERRATE             0.82F       //�������Ƽ��޹��ʣ�80W������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
    #define POKESTEPSPEED                   -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
    #define POKESTEPMINTIMECRACK            265         //������Сʱ������ms��
    #define MAXWORKINGSPEED                 850         //�����˶��ٶȣ����900��
    #define DEPOTABSPITCH                   -8.0F       //������վ��̨pitch���ԽǶ�ֵ��0Ϊˮƽ��-20 ~ 20��  
    #define SNEAKSPEED                      150         //Ǳ���ٶ�
    #define SWINGMODELIMIT                  30          //ҡ��ģʽ�����޷�(�����޸ģ����ø���40�������ģʽ����ʧЧ)
    #define SWINGMODEOMEGA                  90          //ҡ��ģʽ���ٶ�
    #define CIRCLEMODEOMEGA                 300         //ȦȦģʽ���ٶ�
    #define CIRCLEMODEDELAY                 10000       //ȦȦģʽ�ܵ��˺���תʱ��  
    #define QESPINSPEED                     1.0F        //QE�����ٶ�  
    #define MOUSESPINSPEED                  50.0F       //��������ٶ� 
    #define AUTOSHOTDISTANCE                3.2F        //�Զ���������޷�
    #define AUTOSHOTANGLE                   30          //�Զ�����Ƕ��޷�   
    #define BIGSAMPLEOFFSETXPARAM           0.005       //���X�����ƫ�Ƶ��ڱ���
    #define BIGSAMPLEOFFSETYPARAM           0.005       //���X�����ƫ�Ƶ��ڱ���  
    #define ENCODERTOABSANGLEOFFSETPARAM    1         //�ɱ������ӵ��������Ǽ�����̨���ԽǶ�ʱ������֭ƫ��˲������ڽ���ƫ��


#elif INFANTRY == 5               //����

    #define FRICMOTORWORKINGSPEED           264         //Ħ���ֹ����ٶ�(230)
    #define POKESTRUCKDEALLINES             400          //�������������ת��������
    #define CHASSISMAXPOWERRATE             0.82F       //�������Ƽ��޹��ʣ�80W������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
    #define POKESTEPSPEED                   -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
    #define POKESTEPMINTIMECRACK            265         //������Сʱ������ms��
    #define MAXWORKINGSPEED                 850         //�����˶��ٶȣ����900��
    #define DEPOTABSPITCH                   -8.0F       //������վ��̨pitch���ԽǶ�ֵ��0Ϊˮƽ��-20 ~ 20��  
    #define SNEAKSPEED                      150         //Ǳ���ٶ�
    #define SWINGMODELIMIT                  30          //ҡ��ģʽ�����޷�(�����޸ģ����ø���40�������ģʽ����ʧЧ)
    #define SWINGMODEOMEGA                  90          //ҡ��ģʽ���ٶ�
    #define CIRCLEMODEOMEGA                 500         //ȦȦģʽ���ٶ�
    #define CIRCLEMODEDELAY                 10000       //ȦȦģʽ�ܵ��˺���תʱ��  
    #define QESPINSPEED                     1.0F        //QE�����ٶ�  
    #define MOUSESPINSPEED                  50.0F       //��������ٶ� 
    #define AUTOSHOTDISTANCE                3.2F        //�Զ���������޷�
    #define AUTOSHOTANGLE                   30          //�Զ�����Ƕ��޷�  
    #define BIGSAMPLEOFFSETXPARAM           0.005       //���X�����ƫ�Ƶ��ڱ���
    #define BIGSAMPLEOFFSETYPARAM           0.005       //���X�����ƫ�Ƶ��ڱ��� 
    #define ENCODERTOABSANGLEOFFSETPARAM    0.7375         //�ɱ������ӵ��������Ǽ�����̨���ԽǶ�ʱ������֭ƫ��˲������ڽ���ƫ��   

#elif INFANTRY == 6               //���ز�����

    #define FRICMOTORWORKINGSPEED           260         //Ħ���ֹ����ٶ�(230)
    #define POKESTRUCKDEALLINES             400         //�������������ת��������
    #define CHASSISMAXPOWERRATE             0.82F       //�������Ƽ��޹��ʣ�80W������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
    #define POKESTEPSPEED                   -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
    #define POKESTEPMINTIMECRACK            265         //������Сʱ������ms��
    #define MAXWORKINGSPEED                 850         //�����˶��ٶȣ����900��
    #define DEPOTABSPITCH                   -8.0F       //������վ��̨pitch���ԽǶ�ֵ��0Ϊˮƽ��-20 ~ 20��  
    #define SNEAKSPEED                      150         //Ǳ���ٶ�
    #define SWINGMODELIMIT                  30          //ҡ��ģʽ�����޷�(�����޸ģ����ø���40�������ģʽ����ʧЧ)
    #define SWINGMODEOMEGA                  90          //ҡ��ģʽ���ٶ�
    #define CIRCLEMODEOMEGA                 300         //ȦȦģʽ���ٶ�
    #define CIRCLEMODEDELAY                 10000       //ȦȦģʽ�ܵ��˺���תʱ��   
    #define ARTILLERYFRICSPEED              5000        //��Ħ�����ٶ�    
    #define ARTILLERYSHOTCRACK              220         //�ڷ���ʱ����
    #define QESPINSPEED                     1.0F        //QE�����ٶ�  
    #define MOUSESPINSPEED                  50.0F       //��������ٶ�    

#elif INFANTRY == 7               //���ز�����

    #define CHASSISMAXPOWERRATE             0.9F        //�������Ƽ��޹��ʣ�80W������(�����ֵΪ0.9����ʵ�����ƹ���Ϊ0.9*80=72W��
    #define FRICMOTORWORKINGSPEED           275         //Ħ���ֹ����ٶ�(230)
    #define POKESTRUCKDEALLINES             400         //�������������ת��������
    #define POKESTEPMINTIMECRACK            265         //������Сʱ������ms��
    #define POKESTEPSPEED                   -250        //������������ٶȣ����ſ��Ʒ��򣬲�Ҫ����
    #define MOUSESPINSPEED                  50.0F       //��������ٶ�   
    #define AUTOSHOTDISTANCE                4.0F        //�Զ���������޷�
    #define AUTOSHOTANGLE                   30          //�Զ�����Ƕ��޷�
    #define SHOOTUSEOFFTICK                 1600        //��������ʧ��ʱ�䳤�ڴ�������Ϊ�ӵ��ù�
    #define SHOOTUSEOFFNUM                  150         //�ѷ����ӵ����ڴ������ɽ���use up�ж�

#endif
/***************************************   �� �����ֲ���  �� **********************************************/

#if INFANTRY == 1       //��Ħ
    
    #define PITCHMOTORCURRENTPLUSDIR        1           //pitch����̨�����������Ϊ��ʱת������     1 ̧ͷ         0 ��ͷ
    #define YAWMOTORCURRENTPLUSDIR          1           //yaw����̨�����������Ϊ��ʱת������       1 ��ʱ��       0 ˳ʱ��
    #define PITCHMOTORENCODERPLUSEDIR       1           //pitch����̨�������������ʱת������       1 ̧ͷ         0 ��ͷ
    #define YAWMOTORENCODERPLUSEDIR         1           //yaw����̨�������������ʱת������         1 ��ʱ��       0 ˳ʱ��
    #define CANPORT                         1           //ѡ��can�˿�
    #define MOTORTYPE                       1           //�������                                 1 3510        0 35
    #define FRICTYPE                        0           //Ħ��������                               1 3510        0 ��ͨ��ˢ
    #define AUTOSUPPORT                     1           //�Զ�֧�֣����/�Զ������                 1 ֧��        0 ��֧��  
    #define AUTOBIGSAMPLESUPPORT            0           //�Զ����֧��                             1 ֧��        0 ��֧��
    #define AUTOSHOOTSUPPORT                0           //�Զ����֧��                             1 ֧��        0 ��֧��    
    
#elif INFANTRY == 2     //����˹��
    
    #define PITCHMOTORCURRENTPLUSDIR        1           //pitch����̨�����������Ϊ��ʱת������     1 ̧ͷ         0 ��ͷ
    #define YAWMOTORCURRENTPLUSDIR          1           //yaw����̨�����������Ϊ��ʱת������       1 ��ʱ��       0 ˳ʱ��
    #define PITCHMOTORENCODERPLUSEDIR       1           //pitch����̨�������������ʱת������       1 ̧ͷ         0 ��ͷ
    #define YAWMOTORENCODERPLUSEDIR         1           //yaw����̨�������������ʱת������         1 ��ʱ��       0 ˳ʱ��
    #define CANPORT                         1           //ѡ��can�˿�
    #define MOTORTYPE                       1           //�������                                 1 3510        0 35
    #define FRICTYPE                        0           //Ħ��������                               1 3510        0 ��ͨ��ˢ
    #define AUTOSUPPORT                     1           //�Զ�֧�֣����/�Զ������                 1 ֧��        0 ��֧��  
    #define AUTOBIGSAMPLESUPPORT            1           //�Զ����֧��                             1 ֧��        0 ��֧��
    #define AUTOSHOOTSUPPORT                0           //�Զ����֧��                             1 ֧��        0 ��֧��  

#elif INFANTRY == 3     //��ʿ��
    
    #define PITCHMOTORCURRENTPLUSDIR        0           //pitch����̨�����������Ϊ��ʱת������     1 ̧ͷ         0 ��ͷ
    #define YAWMOTORCURRENTPLUSDIR          1           //yaw����̨�����������Ϊ��ʱת������       1 ��ʱ��       0 ˳ʱ��
    #define PITCHMOTORENCODERPLUSEDIR       1           //pitch����̨�������������ʱת������       1 ̧ͷ         0 ��ͷ
    #define YAWMOTORENCODERPLUSEDIR         1           //yaw����̨�������������ʱת������         1 ��ʱ��       0 ˳ʱ��
    #define CANPORT                         1           //ѡ��can�˿�
    #define MOTORTYPE                       1           //�������                                 1 3510        0 35
    #define FRICTYPE                        0           //Ħ��������                               1 3510        0 ��ͨ��ˢ
    #define AUTOSUPPORT                     1           //�Զ�֧�֣����/�Զ������                 1 ֧��        0 ��֧�� 
    #define AUTOBIGSAMPLESUPPORT            1           //�Զ����֧��                             1 ֧��        0 ��֧��
    #define AUTOSHOOTSUPPORT                0           //�Զ����֧��                             1 ֧��        0 ��֧��   

#elif INFANTRY == 4     //��ë
    
    #define PITCHMOTORCURRENTPLUSDIR        0           //pitch����̨�����������Ϊ��ʱת������     1 ̧ͷ         0 ��ͷ
    #define YAWMOTORCURRENTPLUSDIR          0           //yaw����̨�����������Ϊ��ʱת������       1 ��ʱ��       0 ˳ʱ��
    #define PITCHMOTORENCODERPLUSEDIR       1           //pitch����̨�������������ʱת������       1 ̧ͷ         0 ��ͷ
    #define YAWMOTORENCODERPLUSEDIR         1           //yaw����̨�������������ʱת������         1 ��ʱ��       0 ˳ʱ��
    #define CANPORT                         1           //ѡ��can�˿�
    #define MOTORTYPE                       0          //�������                                 1 3510        0 35
    #define FRICTYPE                        0           //Ħ��������                               1 3510        0 ��ͨ��ˢ
    #define AUTOSUPPORT                     0           //�Զ�֧�֣����/�Զ������                 1 ֧��        0 ��֧��  
    #define AUTOBIGSAMPLESUPPORT            0           //�Զ����֧��                             1 ֧��        0 ��֧��
    #define AUTOSHOOTSUPPORT                0           //�Զ����֧��                             1 ֧��        0 ��֧��  

#elif INFANTRY == 5     //����
    
    #define PITCHMOTORCURRENTPLUSDIR        0           //pitch����̨�����������Ϊ��ʱת������     1 ̧ͷ         0 ��ͷ
    #define YAWMOTORCURRENTPLUSDIR          1           //yaw����̨�����������Ϊ��ʱת������       1 ��ʱ��       0 ˳ʱ��
    #define PITCHMOTORENCODERPLUSEDIR       1           //pitch����̨�������������ʱת������       1 ̧ͷ         0 ��ͷ
    #define YAWMOTORENCODERPLUSEDIR         1           //yaw����̨�������������ʱת������         1 ��ʱ��       0 ˳ʱ��
    #define CANPORT                         1           //ѡ��can�˿�
    #define MOTORTYPE                       1           //�������                                 1 3510        0 35
    #define FRICTYPE                        0           //Ħ��������                               1 3510        0 ��ͨ��ˢ
    #define AUTOSUPPORT                     1           //�Զ�֧�֣����/�Զ������                 1 ֧��        0 ��֧�� 
    #define AUTOBIGSAMPLESUPPORT            1           //�Զ����֧��                             1 ֧��        0 ��֧��
    #define AUTOSHOOTSUPPORT                0           //�Զ����֧��                             1 ֧��        0 ��֧��   


#elif INFANTRY == 6     //СӢ��
    
    #define PITCHMOTORCURRENTPLUSDIR        0           //pitch����̨�����������Ϊ��ʱת������     1 ̧ͷ         0 ��ͷ
    #define YAWMOTORCURRENTPLUSDIR          1           //yaw����̨�����������Ϊ��ʱת������       1 ��ʱ��       0 ˳ʱ��
    #define PITCHMOTORENCODERPLUSEDIR       0           //pitch����̨�������������ʱת������       1 ̧ͷ         0 ��ͷ
    #define YAWMOTORENCODERPLUSEDIR         1           //yaw����̨�������������ʱת������         1 ��ʱ��       0 ˳ʱ��
    #define CANPORT                         1           //ѡ��can�˿�
    #define MOTORTYPE                       0           //�������                                 1 3510        0 35
    #define FRICTYPE                        1           //Ħ��������                               1 3510        0 ��ͨ��ˢ
    #define AUTOSUPPORT                     0           //�Զ�֧�֣����/�Զ������                 1 ֧��        0 ��֧�� 
    #define AUTOBIGSAMPLESUPPORT            0           //�Զ����֧��                             1 ֧��        0 ��֧��
    #define AUTOSHOOTSUPPORT                0           //�Զ����֧��                             1 ֧��        0 ��֧��   


#elif INFANTRY == 7     //����
    
    #define PITCHMOTORCURRENTPLUSDIR        1           //pitch����̨�����������Ϊ��ʱת������     1 ̧ͷ         0 ��ͷ
    #define YAWMOTORCURRENTPLUSDIR          1           //yaw����̨�����������Ϊ��ʱת������       1 ��ʱ��       0 ˳ʱ��
    #define PITCHMOTORENCODERPLUSEDIR       1           //pitch����̨�������������ʱת������       1 ̧ͷ         0 ��ͷ
    #define YAWMOTORENCODERPLUSEDIR         1           //yaw����̨�������������ʱת������         1 ��ʱ��       0 ˳ʱ��
    #define CANPORT                         1           //ѡ��can�˿�
    #define MOTORTYPE                       0           //�������                                 1 3510        0 35
    #define FRICTYPE                        0           //Ħ��������                               1 3510        0 ��ͨ��ˢ 

#endif

#define BELLBARKPeriod      100         //����������ʱ�䳤�ȣ�ms��
#define MONITORPERIOD       100         //���������ڣ�ms��
#define GUNSpeed            23.5F       //ǹ�ӵ��ٶ�(m/s)
#define ACCofGravity        9.87F       //acceleration of gravity�������ٶ�

#endif


