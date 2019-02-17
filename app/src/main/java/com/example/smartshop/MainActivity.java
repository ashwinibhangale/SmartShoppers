package com.example.smartshop;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.firebase.client.Firebase;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    Button send,done,sms,next;
    EditText item,qty;
    TextView amt;
    Firebase url;
    float sumamt=0;
    //String name = getIntent().getStringExtra("USERNAME");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Firebase.setAndroidContext(this);

//        send = (Button) findViewById(R.id.send);
        done = (Button) findViewById(R.id.done);
        sms = (Button) findViewById(R.id.sms);
        next = (Button) findViewById(R.id.next);
//        name = (EditText) findViewById(R.id.name);
        item = (EditText) findViewById(R.id.item);
        qty = (EditText) findViewById(R.id.qty);
        amt = (TextView) findViewById(R.id.textView3);

        url = new Firebase("https://smartshopping-c4692.firebaseio.com/");
        next.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String value1,value2,value3;
//                value1 = name.getText().toString();
                value2 = item.getText().toString();
                value3 = qty.getText().toString();

                final int min = 10;
                final int max = 30;

                final int random = new Random().nextInt((max - min) + 1) + min;
                sumamt = sumamt + random;
                String es = Float.toString(sumamt);
                amt.setText("Est.Price:" + es);
//
//                Firebase firebase = url.child("Name");
//                firebase.setValue(value1);
//
//                Firebase firebase1 = url.child("Item");
//                firebase1.setValue(value2);
//
//                Firebase firebase2 = url.child("qty");
//                firebase2.setValue(value3);
                url.child("tobuy").child(value2).setValue(value3);
                item.setText("");
                qty.setText("");

//                url.child(value1).child("Quantity").setValue(value3);


            }
        });
    }
}
