#include <stdio.h>

enum difficultyLevel{easy = 1, medium, hard, extreme, impossible};

int main()
{
	int level = 0;
	enum difficultyLevel i = easy;
	do
	{
		if(level < easy || level > impossible)
		{
			printf("please choose a difficulty level\n");
			for(i = easy; i <= impossible; i++)
			{	
				printf("level - %d\n", i);
			}	
			scanf("%d", &level);
		}
		if(level < easy || level > impossible)
			printf("invalid input, please enter a level between 1 - 5\n");
	}
	while(level < easy || level > impossible);
	return 0;
}

/*
היתרון הוא שזה כמו משתנה אחד שמכיל בתוכו כמה משתנים והם לא בהכרח עוקבים ולכל מיני משתנה יש שם משלו מה שתורם להבנה וגם לסדר של הקוד

בשביל שהספירה תתחיל מ 1 צריך פשוט לאתחל את המשתנה הראשון ל 1 ואז כל השאר הוכים למספרים עוקבים  ואז הספירה תתחיל מ 1

דוג ראשונה: כאשר רוצים קטגוריה של ימים בשבוע
דוג שנייה: כשאר רוצים קטגוריה של חודשים בשנה
*/