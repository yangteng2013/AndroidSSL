package xyz.openhh.ssl;

import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.net.Uri;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.EditText;
import android.widget.RadioGroup;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;

public class DigestActivity extends AppCompatActivity implements View.OnClickListener {

    private static final int REQ_SEL_FILE_CODE = 0x1;

    EditText calculateInput;
    TextView calculateResult;
    ScrollView scrollView;
    RadioGroup radioGroup;

    String selFileName;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_digest);


        findViewById(R.id.md5_calculate).setOnClickListener(this);
        findViewById(R.id.btn_clear).setOnClickListener(this);
        findViewById(R.id.sel_file).setOnClickListener(this);

        calculateInput = (EditText) findViewById(R.id.calculate_input);
        calculateResult = (TextView) findViewById(R.id.calculate_result);
        scrollView = (ScrollView) findViewById(R.id.scroll_view);
        radioGroup = (RadioGroup) findViewById(R.id.radioGroup);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.md5_calculate:
                int checkId = radioGroup.getCheckedRadioButtonId();
                final StringBuilder sBuilder = new StringBuilder("\r\n");
                if (checkId == R.id.rb_md5)
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            if (TextUtils.isEmpty(selFileName))
                                sBuilder.append(NativeSSL.getStrMd5(calculateInput.getText().toString()));
                            else
                                sBuilder.append(NativeSSL.getFileMd5(selFileName));

                            DigestActivity.this.runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    calculateResult.append(sBuilder);
                                }
                            });
                        }
                    }).start();
                else if (checkId == R.id.rb_sha1) {

                }
                scrollView.fullScroll(ScrollView.FOCUS_DOWN);
                break;
            case R.id.btn_clear:
                calculateResult.setText("结果：");
                selFileName = null;
                break;
            case R.id.sel_file:
                openFileManager(v);
                break;
        }
    }


    public void openFileManager(View v) {
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("*/*");
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        try {
            startActivityForResult(Intent.createChooser(intent, "选择文件"), REQ_SEL_FILE_CODE);
        } catch (android.content.ActivityNotFoundException ex) {
            Toast.makeText(this, "没有文件管理器", Toast.LENGTH_SHORT).show();
        }
    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        if (requestCode == REQ_SEL_FILE_CODE && null != data && null != data.getData()) {
            Uri uri = data.getData();
            String filePath = FileUtil.getPath(this, uri);
            if (!TextUtils.isEmpty(filePath)) {
                File file = new File(filePath);
                if (file.exists()) {
                    selFileName = filePath;

                    calculateResult.append("\r\n");
                    calculateResult.append(selFileName);
                }
            } else Toast.makeText(this, "地址为空", Toast.LENGTH_SHORT).show();
        }
        super.onActivityResult(requestCode, resultCode, data);
    }
}
