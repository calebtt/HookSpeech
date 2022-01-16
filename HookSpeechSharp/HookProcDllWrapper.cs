using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace HookSpeechSharp
{
    public class HookProcDllWrapper
    {
        public HookProcDllWrapper()
        {
            HookProcDllImports.AddHooks();
        }

        ~HookProcDllWrapper()
        {
            HookProcDllImports.RemoveHooks();
        }

        public string GetTranslationAlphabet()
        {
            IntPtr p = HookProcDllImports.GetTranslationAlphabet();
            if (p != IntPtr.Zero)
            {
                string? retVal = Marshal.PtrToStringUni(p);
                if (retVal != null)
                    return retVal;
                else
                    return String.Empty;
            }
            return String.Empty;
        }

        public bool SetTranslationAlphabet(string newAlphabet)
        {
            return HookProcDllImports.SetTranslationAlphabet(newAlphabet);
        }

        public string GetWorkingAlphabet()
        {
            IntPtr p = HookProcDllImports.GetWorkingAlphabet();
            if (p != IntPtr.Zero)
            {
                string? retVal = Marshal.PtrToStringAnsi(p);
                if (retVal != null)
                    return retVal;
                else
                    return String.Empty;
            }
            return String.Empty;
        }

        public bool IsHooked()
        {
            return HookProcDllImports.IsHooked();
        }

        public bool RemoveHooks()
        {
            return HookProcDllImports.RemoveHooks();
        }

        public bool AddHooks()
        {
            return HookProcDllImports.AddHooks();
        }
    }
}
