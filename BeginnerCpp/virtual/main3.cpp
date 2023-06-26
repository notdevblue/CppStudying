#include <stdio.h>
#include <memory.h>

class KBase;

typedef void (KBase::* FP)();
// void �� return �ϰ� void �� parameter �� �޴� 
// KBase �� ���� ���� �ּҿ� ���� Ÿ��
// ��� �Լ��� ���� ���� �ּ�

class KBase
{
	int i, j, k;
public:
	KBase()
	{
		i = 1;
		j = 5;
		k = 3;
	}

	void A()
	{
		int* p = reinterpret_cast<int*>(this);

		printf("%d\n", p[1]); // x64 ���� 1 ��� �ȵ�
		printf("%d\n", p[2]); // x64 ���� 1 ��µ�

		void*** po = (void***)this;
		// this �����͸� �������� �������� �����ͷ� ����
		void** pvtbl = (void**)(*po);
		// ���� ���� �����ڸ� �̿��� �������� �����͸� ��
		// �������� �����Ͱ� virtual table ��������
		void* pfn = (void*)pvtbl[0];
		// virtual table ���� ù��° ���� ���� pfn �� ����
		// �� C �� �����Ѱ���

		FP fp;
		memcpy(&fp, &pfn, 4);
		// �׸��� pfn �� ����ִ� �ּҰ��� fp �� ����
		// �������� ������δ� ���� ���簡 ���� �ʾƼ� memcpy ����� 

		(this->*fp)(); // x64 ���� ����� ������ ����

		// x64 ���� �޸� ũ�Ⱑ sizeof(int) * 2 �̱� ����
	}

	virtual void C()
	{
		printf("KBase::C()\r\n");
	}
	virtual void B()
	{
		printf("KBase::B()\r\n");
	}
};

class KDerived : public KBase
{
public:
	virtual void C() override
	{
		printf("KDerived::C()\r\n");
	}
	virtual void D()
	{
		printf("KDerived::D()\r\n");
	}
	void E()
	{
		printf("KDerived::E()\r\n");
	}
};

void main()
{
	KDerived a;
	a.A();
}

// �����Ϸ��� virtual �Լ����� ���� ���ε��� ���ؼ�
// ������ ������ Ÿ�Կ� ���� virtual �Լ��� ����
// table �� �ϳ��� ����
// KBase �� ���ؼ� virtual �Լ����� ���� table �� �����
// KDerived �� ���ؼ��� �ϳ� ����