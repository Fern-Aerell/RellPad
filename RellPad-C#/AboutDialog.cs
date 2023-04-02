using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RellPad_C_
{
    public partial class AboutDialog : Form
    {
        public AboutDialog()
        {
            InitializeComponent();
        }

        private void CloseButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void DeskripsiBox_CursorChanged(object sender, EventArgs e)
        {

        }

        private void DeskripsiBox_MouseMove(object sender, MouseEventArgs e)
        {

        }
    }
}
