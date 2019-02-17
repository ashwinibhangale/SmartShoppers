package com.example.smartshop;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class LoginActivity extends AppCompatActivity {

    private EditText Name;
    private EditText password;
    private TextView Info;
    private Button login;
    private int counter = 3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login2);

        Name = (EditText) findViewById(R.id.username);
        password = (EditText) findViewById(R.id.password);
        login = (Button) findViewById(R.id.button);
        //Info = (TextView)findViewById(R.id.info);
        login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                validate(Name.getText().toString(), password.getText().toString());
            }
        });
    }


    private void validate(String UN, String UP) {
        if ((UN.equals("Admin")) && (UP.equals("1234"))) {
            Intent intent = new Intent(LoginActivity.this,MainActivity.class);
//            intent.putExtra("USERNAME", UN);
               startActivity(intent);
        } else {
            counter--;
            if (counter == 0) {
                login.setEnabled(false);
            }
        }


    }
}