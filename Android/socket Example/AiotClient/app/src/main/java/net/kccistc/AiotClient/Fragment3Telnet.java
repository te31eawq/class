package net.kccistc.AiotClient;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.fragment.app.Fragment;

import java.text.SimpleDateFormat;
import java.util.Date;


public class Fragment3Telnet extends Fragment {
    ClientThread clientThread;
    SimpleDateFormat dateFormat = new SimpleDateFormat("yy MM dd HH:mm:ss");
    ToggleButton toggleButtonConnect;
    ToggleButton toggleButtonLamp;

    ToggleButton toggleButtonPlug;
    Button buttonSend;
    TextView textViewRecv;
    ScrollView scrollViewRecv;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment3telnet, container, false);
        EditText editTextIp = view.findViewById(R.id.editTextLoginIp);
        EditText editTextPort = view.findViewById(R.id.editTextLoginPort);
        scrollViewRecv = view.findViewById(R.id.scrollViewRecv);
        textViewRecv = view.findViewById(R.id.textViewRecv);
        toggleButtonConnect = view.findViewById(R.id.toggleButtonConnect);
        EditText editTextSend = view.findViewById(R.id.editTextSend);
        buttonSend = view.findViewById(R.id.buttonSend);
        toggleButtonLamp = view.findViewById(R.id.toggleButtonLamp);
        toggleButtonPlug = view.findViewById(R.id.toggleButtonPlug);
        buttonSend.setEnabled(false);
        toggleButtonLamp.setEnabled(false);
        toggleButtonPlug.setEnabled(false);
        toggleButtonConnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(toggleButtonConnect.isChecked()) {
                    String Ip = editTextIp.getText().toString();
                    int Port = Integer.parseInt(editTextPort.getText().toString());
                    clientThread = new ClientThread(Ip,Port);
                    clientThread.start();
                    buttonSend.setEnabled(false);
                    toggleButtonConnect.setChecked(false);
                } else {
                    clientThread.stopClient();
                    buttonSend.setEnabled(false);
                    toggleButtonConnect.setChecked(false);
                }
            }
        });

        toggleButtonLamp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(toggleButtonLamp.isChecked()) {
                    toggleButtonLamp.setChecked(false);
                    clientThread.sendData(ClientThread.arduinoId + "LAMPON");
                } else {
                    clientThread.sendData(ClientThread.arduinoId + "LAMPOFF");
                    toggleButtonLamp.setChecked(true);
                }
            }
        });
        toggleButtonPlug.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(toggleButtonPlug.isChecked()) {
                    toggleButtonPlug.setChecked(false);
                    clientThread.sendData(ClientThread.arduinoId + "GASON");
                } else {
                    clientThread.sendData(ClientThread.arduinoId + "GASOFF");
                    toggleButtonPlug.setChecked(true);
                }
            }
        });
        buttonSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String strSend = editTextSend.getText().toString();
                clientThread.sendData(strSend);
                editTextSend.setText("");
            }
        });

        return view;
    }
    void recvDataProcess(String data)
    {
        Date date = new Date();
        String strDate = dateFormat.format(date);
        strDate = strDate + " " + data;
        Log.d("MainHandler",data);
        textViewRecv.append(strDate);
        scrollViewRecv.fullScroll(View.FOCUS_DOWN);

        if(data.indexOf("New connect") != -1) {
            buttonSend.setEnabled(true);
            toggleButtonConnect.setChecked(true);
            toggleButtonLamp.setEnabled(true);
            toggleButtonPlug.setEnabled(true);
            return;
        }else if(data.indexOf("Already logged!") != -1) {
            clientThread.stopClient();
            return;
        } else if(data.indexOf("LAMPON") != -1) {
            toggleButtonLamp.setChecked(true);
        } else if(data.indexOf("LAMPOFF") != -1) {
            toggleButtonLamp.setChecked(false);
        } else if(data.indexOf("GASON") != -1) {
            toggleButtonPlug.setChecked(true);
        } else if(data.indexOf("GASOFF") != -1) {
            toggleButtonPlug.setChecked(false);
        }
    }
}
