package com.example.decodecamera;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraManager;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import com.google.zxing.integration.android.IntentIntegrator;
import com.google.zxing.integration.android.IntentResult;

public class MainActivity extends AppCompatActivity {

    private EditText editText;
    private Button button, btnConverte, buttonScanQr;
    private CameraManager cameraManager;
    private String cameraId;

    private static final int CAMERA_REQUEST_CODE = 100;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        editText = findViewById(R.id.editText);
        button = findViewById(R.id.button);
        btnConverte = findViewById(R.id.btn_converte);
        buttonScanQr = findViewById(R.id.button_scan_qr);

        // Initialize the CameraManager and cameraId
        cameraManager = (CameraManager) getSystemService(CAMERA_SERVICE);
        try {
            cameraId = cameraManager.getCameraIdList()[0];
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }

        buttonScanQr.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                IntentIntegrator integrator = new IntentIntegrator(MainActivity.this);
                integrator.setDesiredBarcodeFormats(IntentIntegrator.QR_CODE);
                integrator.setPrompt("Scan a QR code");
                integrator.setCameraId(0);
                integrator.setBeepEnabled(true);
                integrator.setBarcodeImageEnabled(true);
                integrator.initiateScan();
            }
        });

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String text = editText.getText().toString().trim().toLowerCase();
                if (!text.isEmpty()) {
                    String morseCode = convertToMorseCode(text);
                    flashMorseCode(morseCode);
                }
            }
        });

        btnConverte.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String text = editText.getText().toString().trim().toLowerCase();
                if (!text.isEmpty()) {
                    String repeatedText = new String(new char[5]).replace("\0", text + " ");
                    String morseCode = convertToMorseCode(repeatedText);
                    Intent intent = new Intent(MainActivity.this, DisplayMorseActivity.class);
                    intent.putExtra("MORSE_CODE", morseCode);
                    startActivity(intent);
                }
            }
        });

        // Check and request camera permissions
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.CAMERA}, CAMERA_REQUEST_CODE);
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        IntentResult result = IntentIntegrator.parseActivityResult(requestCode, resultCode, data);
        if (result != null) {
            if (result.getContents() == null) {
                // Handle scan cancel
            } else {
                editText.setText(result.getContents());
            }
        }
    }

    private String convertToMorseCode(String text) {
        StringBuilder morse = new StringBuilder();
        for (char c : text.toCharArray()) {
            switch (c) {
                case 'a':
                    morse.append(".- ");
                    break;
                case 'b':
                    morse.append("-... ");
                    break;
                case 'c':
                    morse.append("-.-. ");
                    break;
                case 'd':
                    morse.append("-.. ");
                    break;
                case 'e':
                    morse.append(". ");
                    break;
                case 'f':
                    morse.append("..-. ");
                    break;
                case 'g':
                    morse.append("--. ");
                    break;
                case 'h':
                    morse.append(".... ");
                    break;
                case 'i':
                    morse.append(".. ");
                    break;
                case 'j':
                    morse.append(".--- ");
                    break;
                case 'k':
                    morse.append("-.- ");
                    break;
                case 'l':
                    morse.append(".-.. ");
                    break;
                case 'm':
                    morse.append("-- ");
                    break;
                case 'n':
                    morse.append("-. ");
                    break;
                case 'o':
                    morse.append("--- ");
                    break;
                case 'p':
                    morse.append(".--. ");
                    break;
                case 'q':
                    morse.append("--.- ");
                    break;
                case 'r':
                    morse.append(".-. ");
                    break;
                case 's':
                    morse.append("... ");
                    break;
                case 't':
                    morse.append("- ");
                    break;
                case 'u':
                    morse.append("..- ");
                    break;
                case 'v':
                    morse.append("...- ");
                    break;
                case 'w':
                    morse.append(".-- ");
                    break;
                case 'x':
                    morse.append("-..- ");
                    break;
                case 'y':
                    morse.append("-.-- ");
                    break;
                case 'z':
                    morse.append("--.. ");
                    break;
                case '1':
                    morse.append(".---- ");
                    break;
                case '2':
                    morse.append("..--- ");
                    break;
                case '3':
                    morse.append("...-- ");
                    break;
                case '4':
                    morse.append("....- ");
                    break;
                case '5':
                    morse.append("..... ");
                    break;
                case '6':
                    morse.append("-.... ");
                    break;
                case '7':
                    morse.append("--... ");
                    break;
                case '8':
                    morse.append("---.. ");
                    break;
                case '9':
                    morse.append("----. ");
                    break;
                case '0':
                    morse.append("----- ");
                    break;
                default:
                    morse.append(" ");
                    break;
            }
        }
        return morse.toString();
    }

    private void flashMorseCode(String morseCode) {
        Handler handler = new Handler();
        long delay = 0;
        long dotDuration = 330; // duration for dot (0.33 seconds)
        long dashDuration = 660; // duration for dash (0.66 seconds)
        long intraCharGap = 330; // gap between dots and dashes within a character
        long interCharGap = 990; // gap between characters
        long wordGap = 2310; // gap between words

        for (char c : morseCode.toCharArray()) {
            if (c == '.') {
                handler.postDelayed(() -> setFlashlight(true), delay);
                delay += dotDuration;
                handler.postDelayed(() -> setFlashlight(false), delay);
                delay += intraCharGap;
            } else if (c == '-') {
                handler.postDelayed(() -> setFlashlight(true), delay);
                delay += dashDuration;
                handler.postDelayed(() -> setFlashlight(false), delay);
                delay += intraCharGap;
            } else if (c == ' ') {
                delay += interCharGap - intraCharGap;
            }
        }
    }

    private void setFlashlight(boolean on) {
        try {
            cameraManager.setTorchMode(cameraId, on);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }
}
