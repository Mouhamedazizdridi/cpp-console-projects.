#include <iostream>  
#include <cstdlib>   
#include <ctime>      
using namespace std;  


enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };


enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };


int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}


string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mult:
        return "x";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}


enOperationType GetRandomOperationType()
{
    return (enOperationType)RandomNumber(1, 4);
}


string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = { "Easy","Medium","Hard","Mixed" };
    return arrQuestionLevelText[QuestionLevel - 1];
}


void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F"); 
    else
    {
        system("color 4F"); 
        cout << "\a";
    }
}


int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mult:
        return Number1 * Number2;
    case enOperationType::Div:
        return (Number2 != 0) ? (Number1 / Number2) : 0;  
    default:
        return Number1 + Number2;
    }
}


struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionsLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};


struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionsLevel QuestionsLevel;
    enOperationType OpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};


stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);

    if (OpType == enOperationType::MixOp)
        OpType = GetRandomOperationType();

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionsLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    case enQuestionsLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        break;
    case enQuestionsLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;
    }

    Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
    Question.QuestionLevel = QuestionLevel;

    return Question;
}


void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
        cout << Quizz.QuestionList[QuestionNumber].Number1 << " "
            << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << " "
            << Quizz.QuestionList[QuestionNumber].Number2 << " = ";

        cin >> Quizz.QuestionList[QuestionNumber].PlayerAnswer;

        if (Quizz.QuestionList[QuestionNumber].PlayerAnswer == Quizz.QuestionList[QuestionNumber].CorrectAnswer)
        {
            cout << "Correct!\n";
            Quizz.NumberOfRightAnswers++;
        }
        else
        {
            cout << "Wrong! Correct Answer: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
            Quizz.NumberOfWrongAnswers++;
        }
    }

    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}


void PlayMathGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestions = 5;  
    Quizz.QuestionsLevel = enQuestionsLevel::EasyLevel;
    Quizz.OpType = enOperationType::MixOp;

    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
    }

    AskAndCorrectQuestionListAnswers(Quizz);

    cout << "\nQuiz Completed! Right Answers: " << Quizz.NumberOfRightAnswers
        << ", Wrong Answers: " << Quizz.NumberOfWrongAnswers << "\n";

    cout << (Quizz.isPass ? "You Passed the Quiz!\n" : "You Failed the Quiz!\n");
}


int main()
{
    srand((unsigned)time(NULL));  // Seed the random number generator.
    PlayMathGame();  
    return 0;  
}