using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace HookSpeechSharp
{
    internal class HookProcDllImports
    {
        private const string DLL_NAME = "HookProcDLL.dll";

        [DllImport(DLL_NAME, CharSet = CharSet.Unicode, ExactSpelling = true, BestFitMapping = false, ThrowOnUnmappableChar = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SetTranslationAlphabet([MarshalAs(UnmanagedType.LPWStr)] string s);
        [DllImport(DLL_NAME, CharSet = CharSet.Unicode, ExactSpelling = true, BestFitMapping = false, ThrowOnUnmappableChar = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetTranslationAlphabet();
        [DllImport(DLL_NAME, CharSet = CharSet.Ansi, ExactSpelling = true, BestFitMapping = false, ThrowOnUnmappableChar = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SetWorkingAlphabet([MarshalAs(UnmanagedType.LPUTF8Str)] string s);
        [DllImport(DLL_NAME, CharSet = CharSet.Ansi, ExactSpelling = true, BestFitMapping = false, ThrowOnUnmappableChar = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetWorkingAlphabet();
        [DllImport(DLL_NAME)]
        public static extern bool AddHooks();
        [DllImport(DLL_NAME)]
        public static extern bool RemoveHooks();
        [DllImport(DLL_NAME)]
        public static extern bool IsHooked();
    }
}
