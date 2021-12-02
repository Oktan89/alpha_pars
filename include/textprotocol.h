#pragma once
//{head} {sbL} {datatime}{sbR}  {poll_p}    {id_p} {rbR}{poll_name}{rbL} {status} {port}
// ***   [29/11/2021 16:01:54] ����� ����� 330357 (��� (���� �) �� ��-5�) ������� ,���� COM31
// ***  [29/11/2021 16:02:25] ����� ����� 190117( ����-16 �� "��������" ���) ���������� � ����� 1
//		����� 12043049 ���������� � ��������, ����� ������ 1
//		����� 10051058 ���������� � ��������, ����� ������ 1
// ***  ����� ������ 190118 - ����.����� � "29/11/2021 16:30:10"

struct PotokolLogSrv
{
    // ��������� ***
    const char* head{"***"};
    // ���������� ������ ����. [
    const char sbL{'['};
    // ���������� ������ ����. ]
    const char sbR{']'};
    //������� ������ ����. (
    const char rbR{'('};
    //������� ������ ����. )
    const char rbL{')'};
    //������� "
    const char marks{'"'};
    //������ ������: �������
    const char* status_start{"�������"};
    //������ ������: ����������
    const char* status_stop{"����������"};
    //��� �����: COM
    const char* portCom{"���� ���"};
    //��� �����: TCP
    const char* postTcp{"���� ���"};
    //����� �����: ����� �����
    const char* poll_p{"����� �����"};
    //����� ������: ����� ������
    const char* p_poll{"����� ������"};
    //��������� �����: ����.�����
    const char* next_poll{"����.�����"};
};