using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace chess
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        public void start()
        {

        }
        private void button1_Click(object sender, EventArgs e)
        {
            if(radioButton1.Checked)
            {
                Form1.mode = 1;
            }
            else if (radioButton2.Checked)
            {
                Form1.mode = 2;
            }
            else if (radioButton3.Checked)
            {
                Form1.mode = 3;
                Form1.ip = textBox1.Text;
            }
        }
    }
}
