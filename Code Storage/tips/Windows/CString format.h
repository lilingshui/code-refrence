//�ڶ�CString���и�ʽ�����ʱ��
//������������ʱ���Ա�����λ������������λС��
//��ЩҪ����

//����
//1>������λ����
CString str;
int a = 1;
str.Format(_T("%03d"), a);

//��a��λ������3λʱ�������ʱ�򽫻���ǰ�油0֪��������λ��
//��a��λ�����ڵ���3λʱ��������ȫ��ʾ��
//�����������Ϊ: 001

//2>������λС��
CString str;
float b = 1.0f;
str.Format(_T("%.2f"), b);

//�����ʾ�����ʱ��ֻ��ʾС��������λ������Ļ�����
//��0
//�����������Ϊ: 1.00