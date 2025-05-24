package Loader;

import Database.QA;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Question {

    public final String text;
    public final int size;
    public final int rightAnswerPos;
    public final List<String> answers;

    private final Random random = new Random();

    public Question(QA qa) {
        text = qa.question;
        int pos = 1;
        int MAX_NUM_OF_QUESTIONS = 5;
        while (pos < MAX_NUM_OF_QUESTIONS && qa.wrongs[pos] != null) {
            pos++;
        }
        size = pos + 1;

        answers = new ArrayList<>();

        ArrayList<Integer> liner = new ArrayList<>();
        for (int i = 0; i < size;) {
            int number = random.nextInt(size);
            if (!liner.contains(number)) {
                liner.add(number);
                i++;
            }
        }

        rightAnswerPos = liner.indexOf(0) + 1;

        for (int number : liner) {
            if (number == 0) {
                answers.add(qa.correct);
            } else {
                answers.add(qa.wrongs[number - 1]);
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();

        builder.append(text).append("\n");
        int pos = 0;
        for (String ans : answers) {
            builder.append(++pos).append(". ").append(ans).append("\n");
        }
        return builder.toString();
    }
}
