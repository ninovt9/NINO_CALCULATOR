
#NINO_CALCULATOR 表达式计算器<br>  

##简介：<br>        
  编译器学习练习，分析计算表达式。<br>  

----------------------------------------------版本分割线------------------------------------------------
 
###version:2.0 <br>    
####更新内容：<br>    
	1.scanner：状态机重写  
	2.parser：改为生成语法树
	
####更新计划:
	1.支持空格
	2.错误处理
	
####使用方法（控制台输入）:

	1+5
	>> 6

	(1+5)*2
	>> 12

####语法：      
	1.词法分析:      
		START		: NUMBER     
					| OPERATOR      
					|        
					;        
		NUMBER		: '0'..'9'+ ;       
		OPERATOR	: '+'|'-'|'*'|'/' ;       

	2.语法分析:
		expression  :	term { ("+" | "-") term }
		term		:	factor { ("*" | "/") factor }
		factor		:	number | "(" expression ")" 


----------------------------------------------版本分割线------------------------------------------------

version:1.0

使用方法:     
在控制台中输入正确表达式（目前不支持错误输入）      
![](https://github.com/ninovt9/NINO_CALCULATOR/blob/master/Source/console_calculator_1.png)     
得出结果      
![](https://github.com/ninovt9/NINO_CALCULATOR/blob/master/Source/console_calculator_2.png)    
错误输入    
![](https://github.com/ninovt9/NINO_CALCULATOR/blob/master/Source/2016.04.03.png)


代码结构:      
NScanner：分析表达式，生成单词流     
NParser：分析单词流，计算表达式结果     
NExpression：表达式类  
NChecker：错误检查。。。

更新情况:     
2016.04.02:控制台简易版     
2016.04.03:增加输入错误检查


