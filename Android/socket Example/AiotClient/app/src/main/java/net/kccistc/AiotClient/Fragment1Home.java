package net.kccistc.AiotClient;

import android.graphics.Color;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;

import androidx.fragment.app.Fragment;

public class Fragment1Home extends Fragment {
    ClientThread clientThread;
    ImageButton imageButtonPlug;
    ImageButton imageButtonLamp;

    MainActivity mainActivity;

    boolean imageButtonLampFlag = false;
    boolean imageButtonPlugFlag = false;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment1home, container, false);

        mainActivity = (MainActivity)getActivity();

        imageButtonLamp = view.findViewById(R.id.imageButtonLamp);
        imageButtonPlug = view.findViewById(R.id.imageButtonPlug);

        imageButtonPlug.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(ClientThread.socket != null) {
                    if (imageButtonPlugFlag)
                    {
                        mainActivity.clientThread.sendData(ClientThread.arduinoId + "GASON");
                        imageButtonPlugFlag = false;
                    }
                    else
                    {
                        mainActivity.clientThread.sendData(ClientThread.arduinoId + "GASOFF");
                        imageButtonPlugFlag = true;
                    }
                }
            }
        });

        imageButtonLamp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(ClientThread.socket != null) {
                    if (imageButtonLampFlag)
                    {
                        mainActivity.clientThread.sendData(ClientThread.arduinoId+"LAMPON");
                        imageButtonLampFlag = false;
                    }
                    else
                    {
                        mainActivity.clientThread.sendData(ClientThread.arduinoId+"LAMPOFF");
                        imageButtonLampFlag = true;
                    }
                }
            }
        });

        return view;
    }
    public void recvDataProcess(String data)
    {
        if(data.indexOf("LAMPON") != -1)
        {
            imageButtonLamp.setImageResource(R.drawable.lamp_on);
            imageButtonLamp.setBackgroundColor(Color.RED);
        }
        else if(data.indexOf("LAMPOFF") != 1)
        {
            imageButtonLamp.setImageResource(R.drawable.lamp_off);
            imageButtonLamp.setBackgroundColor(Color.BLUE);
        }

        if(data.indexOf("GASON") != -1)
        {
            imageButtonPlug.setImageResource(R.drawable.plug_on);
            imageButtonPlug.setBackgroundColor(Color.RED);
        }
        else if(data.indexOf("GASOFF") != 1)
        {
            imageButtonPlug.setImageResource(R.drawable.plug_off);
            imageButtonPlug.setBackgroundColor(Color.BLUE);
        }
    }

}
