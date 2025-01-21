package net.kccistc.telnetclient;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.activity.EdgeToEdge;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.text.SimpleDateFormat;
import java.util.Date;

public class MainActivity extends AppCompatActivity {
    ClientThread clientThread;
    static MainHandler mainHandler;
    ToggleButton toggleButtonConnect;
    ScrollView scrollViewRecv;
    TextView textviewRecv;
    Button buttonSend;
    ToggleButton toggleButtonLamp;
    ToggleButton toggleButtonPlug;
    SimpleDateFormat dateFormat = new SimpleDateFormat("yy-MM-dd HH:mm:ss");
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        EditText editTextIp = findViewById(R.id.editTextTextIp);
        EditText editTextPort = findViewById(R.id.editTextTextPort);
        scrollViewRecv = findViewById(R.id.scrollViewRecv);
        textviewRecv = findViewById(R.id.textViewRecv);

        toggleButtonLamp = findViewById(R.id.toggleButtonLamp);
//        toggleButtonLamp.setEnabled(false);
        toggleButtonLamp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (toggleButtonLamp.isChecked()) {
                    clientThread.sendData(ClientThread.arduinoId + "GASON");
                    toggleButtonLamp.setChecked(false);
                } else {
                    clientThread.sendData(ClientThread.arduinoId + "GASOFF");
                    toggleButtonLamp.setChecked(true);
                }
            }
        });
        toggleButtonPlug = findViewById(R.id.toggleButtonPlug);
//        toggleButtonPlug.setEnabled(false);
        toggleButtonPlug.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (toggleButtonPlug.isChecked()) {
                    clientThread.sendData(ClientThread.arduinoId + "LAMPON");
                    toggleButtonPlug.setChecked(false);
                } else {
                    clientThread.sendData(ClientThread.arduinoId + "LAMPOFF");
                    toggleButtonPlug.setChecked(true);
                }

            }
        });

        toggleButtonConnect = findViewById(R.id.toggleButtonConnect);
        toggleButtonConnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(toggleButtonConnect.isChecked()) {
                    toggleButtonConnect.setChecked(false);
//                    clientThread = new ClientThread();
                    clientThread = new ClientThread(editTextIp.getText().toString(), Integer.parseInt(editTextPort.getText().toString()));
                    clientThread.start();
                } else {
                    clientThread.stopClient();
//                    toggleButtonConnect.setChecked(true);
                    buttonSend.setEnabled(false);
                    toggleButtonLamp.setEnabled(false);
                    toggleButtonPlug.setEnabled(false);
                }
            }
        });

        EditText editTextData = findViewById(R.id.editTextData);
        buttonSend = findViewById(R.id.buttonSend);
        buttonSend.setEnabled(false);
        buttonSend.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                String strSendData = editTextData.getText().toString();
                clientThread.sendData(strSendData);
                editTextData.setText("");
            }
        });
        updateButtonEnable(false);
        mainHandler = new MainHandler();
    }
    class MainHandler extends Handler {
        @Override
        public void handleMessage(@NonNull Message msg) {
            super.handleMessage(msg);
            Bundle bundle = msg.getData();
            String data = bundle.getString("msg");
            Log.d("MainHandler",data);
            if(data.indexOf("New connect") != -1) {
                toggleButtonConnect.setChecked(true);
                updateButtonEnable(true);

                return;
            } else if(data.indexOf("GASON") != -1)
            {
                toggleButtonLamp.setChecked(true);
            } else if(data.indexOf("GASOFF") != -1)
            {
                toggleButtonLamp.setChecked(false);
            } else if(data.indexOf("LAMPON") != -1)
            {
                toggleButtonPlug.setChecked(true);
            } else if(data.indexOf("LAMPOFF") != -1)
            {
                toggleButtonPlug.setChecked(false);
            }
            Date date = new Date();
            String strDate = dateFormat.format(date);
            strDate = strDate + " " + data;
            Log.d("MainHandler",strDate);
            textviewRecv.append(strDate);
            scrollViewRecv.fullScroll(View.FOCUS_DOWN);
        }
    }
    public void updateButtonEnable(boolean bFlag)
    {
        if(bFlag) {
            buttonSend.setEnabled(true);
            toggleButtonLamp.setEnabled(true);
            toggleButtonPlug.setEnabled(true);
        }
        else {
            buttonSend.setEnabled(false);
            toggleButtonLamp.setEnabled(false);
            toggleButtonPlug.setEnabled(false);
        }
    }

}