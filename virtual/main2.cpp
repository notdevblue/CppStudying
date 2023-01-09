#include <stdio.h>

class KBase
{
public:
	// �ı��� ���ε��� ��Ÿ�ӱ��� ����� �ϱ� ������
	// virtual �� ���δ�
	// � Ŭ������ �ٸ� Ŭ������ 
	// base class �� ���ȴٸ� virtual �� �����ִ� ���� ����
	// virtual ���� �ʿ䰡 ���ٸ� �߸� ������ ��
	virtual ~KBase() {
		printf("KBase::~KBase()\r\n");

		//Test2();
		// �����ɶ��� KDerived �� ���� ������ ����
		// �׷��Ƿ� �����ڿ��� virtual �Լ� ȣ�� ��
		// KBase �Լ��� virtual �Լ��� ȣ����
		// �� ������ �Ȱ��� �������ֱ� ���ؼ� �ı��ڿ����� �ڱ� �ڽ��� �Լ��� ȣ����

		// �Ϲ� �Լ����� ȣ��� Test2() �� virtual
		// ����, �ı��ڿ��� �ڽ��� Test2() �� ȣ��

		// �̷��� ������ �ذ��ϱ� ���ؼ� ������ �Ǵ� �ı��ڿ��� virtual �Լ���
		// ȣ�������� �ʾƾ� ��. ���� ������ �Ǵ� ������ ���� �� ����
		
		// Template Method Pattern ������ ��� ��
		// interface �� ������ ���� �Լ����� late binding ��

		DoTest2();
		// �����ڿ� �ı��ڿ��� virtual ȣ���ϸ� �ȵȴٴ°� �� �˰� �ִ� �����
		// ��� �ʿ信 ���� �ı��ڿ��� DoTest2() �� ȣ���Ϸ� ��
		// virtual �� �ƴ�
		// ȣ����
		// virtual �� �ƴ϶� ������ ���ٰ� �Ǵ�
		// �����ϴϱ� �ı��� ȣ�� �������� Base �� Test2() ȣ���
		// ������ Test2() �� pure virtual function
		// ����� ������������ ���� �� ������ �߻���
		// ���� ȣ���� �Լ��� �����Լ��� �ƴϴ���
		// ȣ���� �Լ� ���ο��� �����Լ��� ȣ���Ѵٸ�
		// ������ �߻���
		// �̸� �ذ��� ����� ���������� �������� ����
		// Ŭ���� ����� �ǹ��ִ� �Լ� ȣ���� ���� �ʵ��� �ؾ� ��
		// ���� ��ü�� ������ ���Ŀ� � �ǹ��ִ� �ʱ�ȭ�� �ʿ��ϵ��� �ϸ�
		// ������ interface �Լ��� ����� ���� �ٶ���
		// �����ڿ��� 0 ������ �����ϰ�
		// ���� �Լ� ȣ���ؼ� �ǹ��ִ� �ʱ�ȭ�� ��
	}

	void DoTest2() // Template method pattern �̶�� ��
	{
		Test2();
	}

	void Test1() {
		printf("KBase::Test1()\r\n");

		Test2();
		// Test2() �� virtual �Լ�
		// ������� ��ü Ÿ���� KBase ��� KBase::Test2()
		// KDerived ��� KDerived::Test2()
		// �Ȱ��� ȣ��� �������� ���� �ð��� ���� ȣ��Ǵ� �Լ��� �޶���
	}

	//virtual void Test2() {
	//	printf("KBase::Test2()\r\n");
	//}

	virtual void Test2() = 0;
	// interface �� ������
	// ������ derived class ���� �ؾ� �ϴ� virtual function ��
	// pure virtual function, ���� ���� �Լ� ��� ��
};

class KDerived : public KBase
{
public:
	// ���� Ŭ���������� �� ������ ������ �����°� ����
	virtual ~KDerived() override {
		printf("KDerived::~KDerived()\r\n");
	}

	virtual void Test2() override {

		printf("KDerived::Test2()\r\n");
	}

	void Test3() {
		printf("KDerived::Test3()\r\n");
	}
};

void main()
{
	KBase* pb;
	pb = new KDerived();
	
	//pb->Test2();

	//pb->Test1(); // KDerived Ÿ���̱� ������ Test1() ���� KDerived::Test2() �� ȣ����

	pb->DoTest2();
	// ������ ȣ��Ǵ� �Լ��� ������� ��ü Ÿ�Կ� ���� �޶���

	delete pb;
	// �ı��� ȣ���� 
	// KDerived -> KBase ������ ȣ���
	// ������ ������ ���� KBase -> KDerived ��
	// KDerived �Լ��� ������ ������ �� KBase �� �ı��ڸ� ȣ���ϰ�
	// KBase �ı����� ������ ������ KDerived �ı����� ������ ����
}