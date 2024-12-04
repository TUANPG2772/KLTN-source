package com.example.decodecamera;

import android.os.Bundle;
import android.os.Handler;
import android.widget.RelativeLayout;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class DisplayMorseActivity extends AppCompatActivity {
    private RelativeLayout relativeLayout;
    private Handler handler;
    private int index = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_display_morse);
        relativeLayout = findViewById(R.id.main);
        handler = new Handler();

        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        String morseCode = getIntent().getStringExtra("MORSE_CODE");
        if (morseCode != null) {
            displayMorseCode(morseCode);
        }
    }

    private void displayMorseCode(String morseCode) {
        long delay = 0;

        for (char c : morseCode.toCharArray()) {
            switch (c) {
                case '.':
                    handler.postDelayed(() -> toggleBackground(true), delay);
                    delay += 200;
                    handler.postDelayed(() -> toggleBackground(false), delay);
                    delay += 200;
                    break;
                case '-':
                    handler.postDelayed(() -> toggleBackground(true), delay);
                    delay += 600;
                    handler.postDelayed(() -> toggleBackground(false), delay);
                    delay += 200;
                    break;
                case ' ':
                    delay += 600;
                    break;
                case '/':
                    delay += 1400;
                    break;
            }
        }
    }

    private void toggleBackground(boolean state) {
        if (state) {
            relativeLayout.setBackgroundColor(getResources().getColor(android.R.color.white));
        } else {
            relativeLayout.setBackgroundColor(getResources().getColor(android.R.color.black));
        }
    }
}
