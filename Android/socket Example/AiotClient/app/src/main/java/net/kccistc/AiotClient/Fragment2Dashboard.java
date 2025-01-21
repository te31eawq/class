package net.kccistc.AiotClient;

import android.graphics.Color;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.fragment.app.Fragment;


public class Fragment2Dashboard extends Fragment {

    ClientThread clientThread;

    TextView textViewillu;
    TextView textViewtemp;
    TextView textViewhumi;

    ImageView imageViewLamp;
    ImageView imageViewPlug;
    ImageView imageViewAir;
    Button buttonCondition;

    MainActivity mainActivity;

    Switch switchLamp;
    Switch switchPlug;
    Switch switchAir;

    boolean buttonConditionFlag = false;
    boolean switchLampFlag = false;
    boolean switchPlugFlag = false;
    boolean switchAirFlag = false;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {


        View view = inflater.inflate(R.layout.fragment2dashboard, container, false);

        mainActivity = (MainActivity)getActivity();

        buttonCondition = view.findViewById(R.id.buttonCondition);

        textViewillu = view.findViewById(R.id.textViewillu);
        textViewtemp = view.findViewById(R.id.textViewtemp);
        textViewhumi = view.findViewById(R.id.textViewhumi);

        switchLamp = view.findViewById(R.id.switchLamp);
        switchPlug = view.findViewById(R.id.switchPlug);
        switchAir = view.findViewById(R.id.switchAir);

        imageViewPlug = view.findViewById(R.id.imageViewPlug);
        imageViewLamp = view.findViewById(R.id.imageViewLamp);
        imageViewAir = view.findViewById(R.id.imageViewAir);

        buttonCondition.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(ClientThread.socket != null) {
                    if (buttonConditionFlag)
                    {
                        mainActivity.clientThread.sendData(ClientThread.arduinoId + "GETSENSOR");
                        buttonConditionFlag = false;
                    }
                    else
                    {
                        mainActivity.clientThread.sendData(ClientThread.arduinoId + "GETSENSOR");
                        buttonConditionFlag = true;
                    }
                }
            }
        });

        switchLamp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(ClientThread.socket != null)
                {
                    if(switchLampFlag)
                    {
                        mainActivity.clientThread.sendData(ClientThread.arduinoId + "LAMPOFF");
                        switchLampFlag = false;
                    }
                    else
                    {
                        mainActivity.clientThread.sendData(ClientThread.arduinoId + "LAMPON");
                        switchLampFlag = true;
                    }
                }
            }
        });

        switchPlug.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(ClientThread.socket != null)
                {
                    if(switchPlugFlag)
                    {
                        mainActivity.clientThread.sendData(ClientThread.arduinoId + "GASOFF");
                        switchPlugFlag = false;
                    }
                    else
                    {
                        mainActivity.clientThread.sendData(ClientThread.arduinoId + "GASON");
                        switchPlugFlag = true;
                    }
                }
            }
        });

        switchAir.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(ClientThread.socket != null)
                {
                    if(switchAirFlag)
                    {
                        mainActivity.clientThread.sendData(ClientThread.arduinoId + "AIROFF");
                        switchAirFlag = false;
                    }
                    else
                    {
                        mainActivity.clientThread.sendData(ClientThread.arduinoId + "AIRON");
                        switchAirFlag = true;
                    }
                }
            }
        });
        return view;
    }
    public void recvDataProcess(String data)
    {
        if(data.indexOf("SENSOR") != -1)
        {
            String[] splitLists = data.toString().split("\\[|]|@|\\n");
            if(splitLists[2].indexOf("GETSENSOR") != -1)
            {
                buttonCondition.setTextColor(Color.RED);
            }
            else if(splitLists[2].indexOf("SENSOR") != -1)
            {
                textViewillu.setText(splitLists[3] + "%");
                textViewtemp.setText(splitLists[4] + "C");
                textViewhumi.setText(splitLists[5] + "%");
            }
        }

        if(data.indexOf("GASON") != -1)
        {
            imageViewPlug.setImageResource(R.drawable.blinds_on);
        }
        else if(data.indexOf("GASOFF") != -1)
        {
            imageViewPlug.setImageResource(R.drawable.blinds_off);
        }

        if(data.indexOf("LAMPON") != -1)
        {
            imageViewLamp.setImageResource(R.drawable.led_on);
        }
        else if(data.indexOf("LAMPOFF") != -1)
        {
            imageViewLamp.setImageResource(R.drawable.led_off);
        }

        if(data.indexOf("AIRON") != -1)
        {
            imageViewAir.setImageResource(R.drawable.air_on);
        }
        else if(data.indexOf("AIROFF") != -1)
        {
            imageViewAir.setImageResource(R.drawable.air_off);
        }
    }

}
