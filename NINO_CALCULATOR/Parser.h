#pragma once

#include "Token.h"
#include "Scanner.h"

#include <vector>
#include <memory>




namespace calculator
{
	class AST
	{
	public:
		AST();
		AST(Token root);
		AST(AST left, Token root, AST right);

	public:
		std::shared_ptr<AST> left_;
		std::shared_ptr<AST> right_;
		Token token_;
	};


	class Parser
	{
	// expression : term { ("+" | "-") term }
	// term : factor { ("*" | "/") factor }
	// factor : number | "(" expression ")" 


	//��getToken��Ϊvector��iterʵ��...��ô��ԭ���Ĵ���ȫ���ˡ�����
	//����vczh˵�ĺ��е���Ӧ����Ժ������ԣ�������class��ʵ��
	//�走�� �ع�֮ǰ�Ȳ�дunit class�ˣ�



	public:
		Parser(const std::string &expression);

	public:
		AST GetAST();
		AST GetNodeExp(std::vector<Token>::iterator iter);
		AST GetNodeTerm(std::vector<Token>::iterator iter);
		AST GetNodeFactor(std::vector<Token>::iterator iter);


		//AST GetAST();
		//AST GetNodeExp(Token token);		
		//AST GetNodeTerm(Token token);		
		//AST GetNodeFactor(Token token);	

	private:
		AST ast_;
		Scanner scanner_;		
		std::vector<Token> tokenList_;
	};
}



